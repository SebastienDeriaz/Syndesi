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
PAYLOADS_CPP_TEMPLATE_FILE = join(dirname(__file__), "payloads_template.cpp.txt")
PAYLOADS_CPP_OUTPUT_FILE = join(dirname(__file__), "../C++/syndesicp/src/payloads.cpp")

## Callbacks
FRAME_MANAGER_CALLBACKS_CPP_TEMPLATE_FILE = join(dirname(__file__), "framemanagercallbacks_template.cpp.txt")
FRAME_MANAGER_CALLBACKS_CPP_OUTPUT_FILE = join(dirname(__file__), "../C++/syndesicp/src/framemanagercallbacks.cpp")
CALLBACKS_HPP_TEMPLATE_FILE = join(dirname(__file__), "callbacks_template.hpp.txt")
CALLBACKS_HPP_OUTPUT_FILE = join(dirname(__file__), "../C++/syndesicp/include/callbacks.hpp")
CALLBACKS_CONFIGURATION_HPP_TEMPLATE_FILE = join(dirname(__file__), "callbacks_configuration_template.hpp.txt")
CALLBACKS_CONFIGURATION_HPP_OUTPUT_FILE = join(dirname(__file__), "../C++/syndesicp/user_config/callbacks_config.hpp")

# Python
COMMANDS_PY_TEMPLATE_FILE = join(dirname(__file__), "payloads_template.py")
COMMANDS_PY_OUTPUT_FILE = join(dirname(__file__), "../Python/syndesi/syndesi/payloads.py")


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
        # Create C++ source
        replace(PAYLOADS_CPP_TEMPLATE_FILE, PAYLOADS_CPP_OUTPUT_FILE, {
            "date" : datetime.strftime(datetime.now(), "%y-%m-%d %H:%M:%S"),
            "file" : Path(__file__).name,
            "commands_names_switch" : cpp.commands_names_switch(),
            "commands_ids" : cpp.commands_ids()
        })

        # Create C++ callbacks configuration file (for the user to edit)
        replace(CALLBACKS_CONFIGURATION_HPP_TEMPLATE_FILE, CALLBACKS_CONFIGURATION_HPP_OUTPUT_FILE, {
            "date" : datetime.strftime(datetime.now(), "%y-%m-%d %H:%M:%S"),
            "file" : Path(__file__).name,
            "request" : cpp.defines(request=True),
            "reply" : cpp.defines(request=False)
        })

        

        # Create C++ callbacks source file
        replace(FRAME_MANAGER_CALLBACKS_CPP_TEMPLATE_FILE, FRAME_MANAGER_CALLBACKS_CPP_OUTPUT_FILE, {
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
