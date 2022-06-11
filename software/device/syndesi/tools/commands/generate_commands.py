"""
@Author: Sébastien Deriaz
@Date: 06.06.2022

Commands.py script
Generate commands.hpp and commands.py files from commands.yaml file
Those files contains the enums for each command of the Syndesi project
"""

import yaml
from datetime import datetime

COMMANDS_DESCRIPTION_FILE = "./commands.yaml"
COMMANDS_HPP_OUTPUT_FILE = "./../../include/commands.hpp"
COMMANDS_PY_OUTPUT_FILE = "./commands.py"



# Yaml keys
COMMANDS_KEY = "Commands"
COMMAND_ALIAS = "alias"
COMMAND_VALUE = "value"
COMMAND_COMMENT  = "comment"

# Other
REPLACE_KEY = "#1#"

# C++
CPP_FORMAT = lambda X, Y : ''.join([f"    {x} = 0x{y:04X}{',' if i < len(X) - 1 else ''}\n" for i, (x,y) in enumerate(zip(X,Y))])
CPP_CONTENT = f"""
/* THIS FILE IS GENERATED AUTOMATICALLY
*  DO NOT EDIT
*  This file has been written by the script {__file__}
*  date : {datetime.strftime(datetime.now(), "%d.%m.%y")}
*/

#include "syndesi_types.hpp"

namespace syndesi {{

typedef enum Syndesi_commands : syndesi_cmd {{
{REPLACE_KEY}}};

}}
"""

# Python
PY_FORMAT = lambda X, Y : ''.join([f"    {x} = 0x{y:04X}\n" for x,y in zip(X,Y)])
PY_CONTENT = f"""
\"\"\"
THIS FILE IS GENERATED AUTOMATICALLYDO NOT EDIT
This file has been written by the script {__file__}
date : {datetime.strftime(datetime.now(), "%d.%m.%y")}
\"\"\"
from enum import Enum

class Commands(Enum):
{REPLACE_KEY}
"""



def main():
    # Read the description file
    with open(COMMANDS_DESCRIPTION_FILE, 'r', encoding='utf-8') as desc:
        desc_content = yaml.full_load(desc)

        aliases = [cmd[COMMAND_ALIAS] for cmd in desc_content[COMMANDS_KEY]]
        values = [cmd[COMMAND_VALUE] for cmd in desc_content[COMMANDS_KEY]]

        with open(COMMANDS_HPP_OUTPUT_FILE, 'w', encoding='utf-8') as f:
            enum = CPP_FORMAT(aliases, values)
            content = CPP_CONTENT.replace('#1#', enum)
            f.write(content)
        
        with open(COMMANDS_PY_OUTPUT_FILE, 'w', encoding='utf-8') as f:
            enum = PY_FORMAT(aliases, values)
            content = PY_CONTENT.replace('#1#', enum)

            f.write(content)


if __name__ == '__main__':
    main()