
"""
THIS FILE IS GENERATED AUTOMATICALLYDO NOT EDIT
This file has been written by the script .\generate_commands.py
date : 08.06.22
"""
from enum import Enum

class Commands(Enum):
    DEVICE_DISCOVER = 0x0000
    REGISTER_READ = 0x0010
    REGISTER_WRITE = 0x0020
    SPI_READ = 0x0030
    SPI_WRITE = 0x0040
    I2C_READ = 0x0050

