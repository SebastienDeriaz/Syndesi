"""
C++ code generation class
"""

from commands import Command
from os.path import join, dirname
from utilities import replace_str
from settings import types

with open(join(dirname(__file__), "payload_class_template.cpp.txt")) as f:
    CPP_PAYLOAD_TEMPLATE = f.read()

TAB = 4*' '

class CPP():
    def __init__(self, commands_list : list[Command]):
        """
        Instanciate a CPP code generation class with a list of Command objects
        """
        self._commands = commands_list

    def commands_enum(self):
        """
        Return an enum of commands
        """

        output = ''
        for i, command in enumerate(self._commands):
            if i > 0:
                output += ',\n'
            output += f"{TAB}{command.alias} = 0x{command.ID:04x}"
        
        return output

    def payloads(self):
        """
        Generate the class description for each payload
        """ 

        cpp_type_conversion = {
            types.double : lambda field : f"double {field.name};",
            types.uint : lambda field : f"uint{field.size*8}_t {field.name};",
            types.int  : lambda field : f"int{field.size*8}_t {field.name};",
            types.float : lambda field : f"float {field.name}",
            types.enum : lambda field : f"enum {field.name}_t {field.enum}{field.name};"
        }

        output = ''

        for command in self._commands:
            parse = ''
            build = ''
            variables = ''
            argument_constructor = ''
            arguments = ''
            fields = ''
            length = 2*TAB + 'return '
            for fields in filter(None, [command.request_fields, command.reply_fields]):
                for i, field in enumerate(fields):
                    if i > 0:
                        arguments += ', '
                        argument_constructor += ', '
                        length += ' + '


                    if field.type in [types.double, types.int, types.uint, types.float, types.enum]:
                        # Copy with endian conversion
                        parse += 2*TAB + f"pos += ntoh(payloadBuffer.data + pos, (char*)&{field.name}, {field.size});\n"
                        build += 2*TAB + f"pos += hton((char*)&{field.name}, payloadBuffer.data + pos, {field.size});\n"
                        variables += TAB + cpp_type_conversion[field.type](field)
                        arguments += cpp_type_conversion[field.type](field).replace(';', '')
                        
                    elif field.type in [types.char]:
                        # Array
                        parse += "#if COPY_ARRAY_ARGUMENTS\n"
                        parse += 2*TAB + f"memcpy({field.name}.data, payloadBuffer.data + pos, {field.size});\n"
                        parse += "#else\n"
                        parse += 2*TAB + f"{field.name}.data = payloadBuffer.data + pos;\n"
                        parse += "#endif\n"
                        parse += 2*TAB + f"{field.name}.length = {field.size};\n"

                        # The build always needs to copy since we don't know the buffer in advance
                        build += 2*TAB + f"memcpy(payloadBuffer.data + pos, {field.name}.data, {field.size});\n"
                    else:
                        raise ValueError(f"Unsupported type : {field.type}")
                
                    output += replace_str(CPP_PAYLOAD_TEMPLATE, {
                        "alias" : command.alias,
                        "values" : variables,
                        "parse_function" : parse,
                        "length_function" : length,
                        "build_function"  : build,
                        #"constructor" : TAB + f"{self.name}({arguments}) : {argument_constructor}{{}}"
                        "constructor" : '',
                        "command" : TAB+f"cmd_t getCommand() {{return 0x{command.ID:04X};}}"
                    })
                length += str(field.size)
                argument_constructor += f"{field.name}({field.name})"
            length += ';'
        return output

    def defines(self, request):
        """
        Generate a list of defines for each command

        //#define USE_command1_callback 
        //#define USE_command2_callback 
        ...

        Parameters
        ----------
        request : bool
            Request mode / reply mode

        Returns
        -------
        output : str
        """

        output = ''

        i = 0
        for command in self._commands:
            if command.has_request:
                output += f'//#define USE_{command.alias.upper()}_REQUEST_CALLBACK\n'
            if command.has_reply:
                output += f'//#define USE_{command.alias.upper()}_REPLY_CALLBACK\n'
        return output

    def switch(self, request):
        """
        Returns a switch statement to test each command case

        Request mode is for the processing of requests commands

        Parameters
        ----------
        request : bool
            

        Returns
        -------
        output : str
        """
        TAB = 4
        output = ''

        for command in self._commands:            
            if request and command.has_request:
                output += f'#ifdef USE_{command.alias.upper()}_REQUEST_CALLBACK\n'                
                output += ' '*2*TAB + f'case commands::{command.alias}:\n'
                #output += ' '*3*TAB + f'if({command}_{command_type} != NULL) {{\n'
                output += ' '*4*TAB + f'{command.alias}_request request(payloadBuffer);\n'
                output += ' '*4*TAB + f'{command.alias}_reply reply;\n'
                output += ' '*4*TAB + f'{command.alias}_request_callback(request, reply);\n'
                #output += ' '*3*TAB + '}\n'
                output += ' '*3*TAB + f'break;\n'
                output += '#endif\n'
            elif not request and command.has_reply:
                output += f'#ifdef USE_{command.alias.upper()}_REPLY_CALLBACK\n'
                output += ' '*2*TAB + f'case commands::{command.alias}:\n'
                #output += ' '*3*TAB + f'if({command}_{command_type} != NULL) {{\n'
                output += ' '*4*TAB + f'{command.alias}_reply reply(payloadBuffer);\n'
                output += ' '*4*TAB + f'{command.alias}_reply_callback(reply);\n'
                #output += ' '*3*TAB + '}\n'
                output += ' '*3*TAB + f'break;\n'
                output += '#endif\n'
        return output

    def callbacks(self):
        """
        Inits callbacks defines at NULL

        #define DEVICE_DISCOVER_REQUEST_CALLBACK NULL
        ...

        Returns
        -------
        defines : str
        """

        TAB = 4
        output = ''
        for command in self._commands:
            if command.has_request:
                output += f'#ifdef USE_{command}_REQUEST_CALLBACK\n'
                output += TAB*' ' + f'void {command}_request_callback({command}_request& request, {command}_reply& reply);\n'
                output += f'#endif\n'
            if command.has_reply:
                output += f'#ifdef USE_{command}_REPLY_CALLBACK\n'
                output += TAB*' ' + f'void {command}_reply_callback({command}_reply& reply);\n'
                output += f'#endif\n'
        return output





