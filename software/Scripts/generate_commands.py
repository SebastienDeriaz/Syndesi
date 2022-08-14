"""
@Author: Sébastien Deriaz
@Date: 06.06.2022

Commands.py script
Generate code based on the commands.yaml file
Those files contains the enums for each command of the
Syndesi project as well as the structs corresponding to each content

A template (.txt) is used for each file and keys (>>>...<<<) are replaced by their corresponding content
"""

import yaml
from datetime import datetime
from os.path import join, dirname
from pathlib import Path    
from utilities import replace, replace_str
from commands import Command
from settings import YAML_ALIAS_KEY, YAML_COMMANDS_LIST_KEY, YAML_SETTINGS_KEY
from cpp import CPP
import re

# Files
COMMANDS_DESCRIPTION_FILE = join(dirname(__file__), "commands.yaml")
# C++
PAYLOADS_HPP_TEMPLATE_FILE = join(dirname(__file__), "payloads_template.hpp.txt")
PAYLOADS_HPP_OUTPUT_FILE = join(dirname(__file__), "../C++/syndesicp/include/payloads.hpp")

## Callbacks
CALLBACKS_CPP_TEMPLATE_FILE = join(dirname(__file__), "callbacks_template.cpp.txt")
CALLBACKS_CPP_OUTPUT_FILE = join(dirname(__file__), "../C++/syndesicp/src/callbacks.cpp")
CALLBACKS_HPP_TEMPLATE_FILE = join(dirname(__file__), "callbacks_template.hpp.txt")
CALLBACKS_HPP_OUTPUT_FILE = join(dirname(__file__), "../C++/syndesicp/include/callbacks.hpp")
CALLBACKS_CONFIGURATION_HPP_TEMPLATE_FILE = join(dirname(__file__), "callbacks_configuration_template.hpp.txt")
CALLBACKS_CONFIGURATION_HPP_OUTPUT_FILE = join(dirname(__file__), "../C++/syndesicp/user_config/callbacks_configuration.hpp")

# Python
COMMANDS_PY_TEMPLATE_FILE = join(dirname(__file__), "payloads_template.py")
COMMANDS_PY_OUTPUT_FILE = join(dirname(__file__), "../Python/syndesi/syndesi/payloads.py")

# class Field():
#     def __init__(self, field_name, field_size):
#         """
#         Frame field
#         - Constant size
#             - Integer
#             - Array
#         - Variable size (with the name of another field)

#         Parameters
#         ----------
#         field_name : str
#         field_size : str
#         """
#         self.name = field_name
#         # Check for i8, u16, a9 etc...
#         match = re.match('([uia])([0-9]+)', field_size)
#         if match is None:
#             # length corresponding to a preceding value
#             self.variable_length_name = field_size
#             self.variable_length = True
#             self.bytes = field_size
#             self.endian_conversion = False
#         else:
#             self.variable_length = False
#             # i8, u32, etc...
#             if match[1] == 'a':
#                 # Array
#                 self.is_array = True
#                 self.array_length = match[2]
#                 self.bytes = self.array_length
#                 self.endian_conversion = False
#             else:
#                 # Integer
#                 self.is_array = False
#                 self.signed = match[1] == 'i'
#                 self.Nbits = int(match[2])
#                 self.bytes = self.Nbits // 8
#                 self.endian_conversion = True

#     def cpp(self):
#         """
#         Returns a C++ description of the field
        
#         Returns
#         -------
#         output : str
#         """

#         if self.variable_length or self.is_array:
#             output =  f'Buffer {self.name}'
#         else:
#             # Integer
#             if not self.signed:
#                 output = 'u'
#             if self.Nbits in [8, 16, 32, 64]:
#                 output += f'int{self.Nbits}_t '
#             else:
#                 raise ValueError(f"Invalid integer size : {self.Nbits}")
#             output += f'{self.name}'
#         return output
    
#     def python(self):
#         """
#         Returns a Python description of the field
#         """
#         output = ''
#         if self.variable_length:
#             output =  f'{self.name} : bytearray'
#         elif self.is_array:
#             output = f'{self.name} : bytes({self.array_length})'
#         else:
#             # Integer
#             output = f'{self.name} : int'
#         return output



# class FrameContent():
#     def __init__(self, fields : dict, name, command_ID):
#         """
#         Instance of a frame content (multiple fields)
        
#         Parameters
#         ----------
#         fields : dict
#             Dictionary of fields by name
#         """
#         self.fields = fields
#         self.name = name
#         self.command_ID = command_ID

#     def cpp_struct(self):
#         """
#         Return a C++ struct content with a constructor for the current Frame
#         """
        
#         parse = ''
#         build = ''
#         argument_constructor = ''
#         arguments = ''
#         TAB = ' '*4
#         fields = ''
#         length = 2*TAB + 'return '
#         if not self.fields is None:
            

#             for i, (field_name, field_size) in enumerate(self.fields.items()):
#                 if i > 0:
#                     arguments += ', '
#                     argument_constructor += ', '
#                     length += ' + '
#                 field = Field(field_name, field_size)
#                 fields += TAB + field.cpp() + ";\n"
#                 if field.endian_conversion:
#                     parse += 2*TAB + f"pos += ntoh(payloadBuffer.data + pos, (char*)&{field.name}, {field.bytes});\n"
#                     build += 2*TAB + f"pos += hton((char*)&{field_name}, payloadBuffer.data + pos, {field.bytes});\n"
#                 else:
#                     parse += "#if COPY_ARRAY_ARGUMENTS\n"
#                     parse += 2*TAB + f"memcpy({field.name}.data, payloadBuffer.data + pos, {field.bytes});\n"
#                     parse += "#else\n"
#                     parse += 2*TAB + f"{field.name}.data = payloadBuffer.data + pos;\n"
#                     parse += "#endif\n"
#                     parse += 2*TAB + f"{field.name}.length = {field.bytes};\n"
#                     # The build always needs to copy since we don't know the buffer in advance
#                     build += 2*TAB + f"memcpy(payloadBuffer.data + pos, {field.name}.data, {field.bytes});\n"


                

#                 length += str(field.bytes)

#                 argument_constructor += f"{field.name}({field.name})"



#                 arguments += f"{field.cpp()}"
        
#             length += ';'

#             output = replace_str(CPP_PAYLOAD_TEMPLATE, {
#                 "name" : self.name,
#                 "values" : fields,
#                 "parse_function" : parse,
#                 "length_function" : length,
#                 "build_function"  : build,
#                 #"constructor" : TAB + f"{self.name}({arguments}) : {argument_constructor}{{}}"
#                 "constructor" : '',
#                 "command" : TAB+f"cmd_t getCommand() {{return 0x{self.command_ID:04X};}}"
#             })
#         else:
#             output = replace_str(CPP_PAYLOAD_TEMPLATE, {
#                 "name" : self.name,
#                 "values" : '',
#                 "parse_function" : '',
#                 "length_function" : 2*TAB+"return 0;",
#                 "build_function"  : '',
#                 "constructor" : '',
#                 "command" : TAB+f"cmd_t getCommand() {{return 0x{self.command_ID:04X};}}"
#             })
#         return output
    
#     def python_struct(self):
#         """
#         Return a Python class to describe the current frame
#         """
#         TAB = ' '*4
#         init = ''
#         struct = ''
#         writebuffer = ''
#         readbuffer_start = ''
#         readbuffer_end = ''
#         readbuffer = ''
        
#         if not self.fields is None:
#             for i, (name, size) in enumerate(self.fields.items()):
#                 field = Field(name, size)
#                 if i > 0:
#                     init += '\n'
#                     readbuffer_start += ', '
#                     readbuffer_end += ', '
#                     struct += ',\n'
#                     writebuffer += ', '

                
#                 readbuffer_start += f'self.{field.name}'
#                 readbuffer_end += f'parsed_values.{field.name}'
#                 writebuffer += f'{field.name} = self.{field.name}'
#                 struct += TAB*2
#                 if field.variable_length:
#                     struct += f"\"{field.name}\" / Array(this.{field.bytes}, Byte)"
#                     field_type = 'bytearray'
#                 elif field.is_array:
#                     struct += f"\"{field.name}\" / Array({field.bytes}, Byte)"
#                     field_type = 'bytearray'
#                 else:
#                     struct += f"\"{field.name}\" / Int{field.Nbits}{'s' if field.signed else 'u'}{'b' if FRAME_ENDIAN == 'big' else 'l'}"
#                     field_type = 'int'

#                 init += TAB + f'{field.name} : {field_type} = None'
#             readbuffer = TAB*3 + "parsed_values = self.format.parse(buffer)\n"
#             readbuffer += TAB*3 + f"{readbuffer_start} = {readbuffer_end}"
#         else:
#             readbuffer = TAB*3 + 'pass # No values to set from buffer'
#             output = ''

#         output = f"""
# @dataclass
# class {self.name}(Payload):
# {init}
#     command_ID = 0x{self.command_ID:04X}
#     format = Struct(
# {struct}
#     )
#     def parse(self, buffer=None):
#         \"\"\"
#         Create a payload instance from buffer
#         \"\"\"

#         if not buffer is None:
#             # Initialize variables with input buffer
# {readbuffer}
#     def value(self):
#         buffer = self.format.build(dict({writebuffer}))
#         return buffer
#     """
#         return output

# def python_enum(values : dict):
#     """
#     Returns a Python enum with the given values

#     Parameters
#     ----------
#     values : dict

#     Returns
#     -------
#     output : str
    
#     """
#     TAB = 4
#     output = ''
#     for i, (command, value) in enumerate(values.items()):
#         if i > 0:
#             output += '\n'
#         output += ' '*TAB + f'{command} = 0x{value:04X}'
#     return output
    
#     def cpp_payloads(self):
#         """
#         Returns a list of structs to manage frame contents

#         typedef struct {
#             unsigned char A;
#             unsigned short length;
#             std::vector<unsigned char> data; //size : length
#             command_name_content(char* buffer, size_t bufferLength) {
#                 // assign values
#             }
#         }command_name_reply/request

#         Returns
#         -------
#         output : str        
#         """

#         output = ''
#         TAB = 4

#         for request_fields, reply_fields in zip(self.request_content.values(), self.reply_content.values()):
#             # If any of the commands contains a field, we declare both (in theory this is every command except NO_COMMAND)
#             if request_fields.fields is not None or reply_fields.fields is not None:
#                 for content in [request_fields, reply_fields]:
#                     output += content.cpp_struct()
        
#         return output






#     def python_commands(self):
#         """
#         Returns a Python implementation of the commands enum
        
#         Returns
#         -------
#         output : str
#         """
        
#         return python_enum(self.commands)

#     def python_contents(self):
#         """
#         Returns a list of Python classes to manage frame contents

#         class command_name_content
#             name : str
#             length : int
#             buffer : bytearray
#             fixed_size_buffer : bytes(10)

#         Also creates a dictionary of classes corresponding 

#         Returns
#         -------
#         output : str  
        
#         """
#         output = ''

#         for request_fields, reply_fields in zip(self.request_content.values(), self.reply_content.values()):
#             for content in [request_fields, reply_fields]:
#                 output += content.python_struct()
#         return output

#     def python_frames_match(self):
#         """
#         Returns a dictionary to match a command ID with a command class

#         Returns
#         -------
#         output : str
#         """
#         TAB = ' '*4

#         output = ''.join([TAB + f"Commands_IDs.{cmd}.value : {cmd}_reply,\n" for cmd in self.commands])
#         return output



def main():
    # Read the description file
    with open(COMMANDS_DESCRIPTION_FILE, 'r', encoding='utf-8') as desc:
        desc_content = yaml.full_load(desc)
        # Load commands
        commands = [Command(cmd) for cmd in desc_content[YAML_COMMANDS_LIST_KEY]]
        # Load special values

        settings = desc_content[YAML_SETTINGS_KEY]

        cpp = CPP(commands)
        # Create C++ header
        replace(PAYLOADS_HPP_TEMPLATE_FILE, PAYLOADS_HPP_OUTPUT_FILE, {
            "date" : datetime.strftime(datetime.now(), "%y-%m-%d %H:%M:%S"),
            "file" : Path(__file__).name,
            "commands" : cpp.commands_enum(),
            "payloads" : cpp.payloads()
        })

        # Create C++ callbacks configuration file (for the user to edit)
        replace(CALLBACKS_CONFIGURATION_HPP_TEMPLATE_FILE, CALLBACKS_CONFIGURATION_HPP_OUTPUT_FILE, {
            "date" : datetime.strftime(datetime.now(), "%y-%m-%d %H:%M:%S"),
            "file" : Path(__file__).name,
            "request" : cpp.defines(request=True),
            "reply" : cpp.defines(request=False)
        })

        

        # Create C++ callbacks source file
        replace(CALLBACKS_CPP_TEMPLATE_FILE, CALLBACKS_CPP_OUTPUT_FILE, {
            "date" : datetime.strftime(datetime.now(), "%y-%m-%d %H:%M:%S"),
            "file" : Path(__file__).name,
            "switch_request" : cpp.switch(request=True),
            "switch_reply" : cpp.switch(request=False)
        })

        # Create C++ callbacks header file
        replace(CALLBACKS_HPP_TEMPLATE_FILE, CALLBACKS_HPP_OUTPUT_FILE, {
            "date" : datetime.strftime(datetime.now(), "%y-%m-%d %H:%M:%S"),
            "file" : Path(__file__).name,
            "callbacks" : cpp.callbacks()
        })

        # # Create Python module
        # replace(COMMANDS_PY_TEMPLATE_FILE, COMMANDS_PY_OUTPUT_FILE, {
        #     "date" : datetime.strftime(datetime.now(), "%y-%m-%d %H:%M:%S"),
        #     "file" : Path(__file__).name,
        #     "commands" : commands.python_commands(),
        #     "payloads" : commands.python_contents(),
        #     "special_values" : special_values.python(),
        #     "endian" : f"FRAME_ENDIAN = \"{FRAME_ENDIAN}\"",
        #     "payload_match" : commands.python_frames_match()
        # })

if __name__ == '__main__':
    main()