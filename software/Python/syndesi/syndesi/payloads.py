"""
THIS FILE IS GENERATED AUTOMATICALLYDO NOT EDIT
This file has been written by the script generate_commands.py
date : 22-08-13 09:50:36
"""

from typing import TypedDict
from construct import *
from enum import Enum
from dataclasses import dataclass

FRAME_ENDIAN = "big"

class Commands(Enum):
    NO_COMMAND = 0x0000
    DEVICE_DISCOVER = 0x0001
    REGISTER_READ_16 = 0x0100
    REGISTER_WRITE_16 = 0x0101
    SPI_READ_WRITE = 0x0110
    SPI_WRITE_ONLY = 0x0111
    I2C_READ = 0x0120
    I2C_WRITE = 0x0121

@dataclass
class Payload():
    def value(self) -> bytearray:
        """
        Return bytearray value of the frame    

        Returns
        -------
        output : bytearray
        """
        raise NotImplementedError("Cannot use function directly")

    def parse(self, buffer : bytearray):
        """
        Parse frame from a bytearray buffer

        Parameters
        ----------
        buffer : bytearray
        """
        raise NotImplementedError("Cannot use function directly")


@dataclass
class NO_COMMAND_request(Payload):

    command_ID = 0x0000
    format = Struct(

    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            pass # No values to set from buffer
    def value(self):
        buffer = self.format.build(dict())
        return buffer
    
@dataclass
class NO_COMMAND_reply(Payload):

    command_ID = 0x0000
    format = Struct(

    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            pass # No values to set from buffer
    def value(self):
        buffer = self.format.build(dict())
        return buffer
    
@dataclass
class DEVICE_DISCOVER_request(Payload):

    command_ID = 0x0001
    format = Struct(

    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            pass # No values to set from buffer
    def value(self):
        buffer = self.format.build(dict())
        return buffer
    
@dataclass
class DEVICE_DISCOVER_reply(Payload):
    mac : int = None
    syndesi_protocol_version : int = None
    device_version : int = None
    name_length : int = None
    name : bytearray = None
    description_length : int = None
    description : bytearray = None
    command_ID = 0x0001
    format = Struct(
        "mac" / Int64ub,
        "syndesi_protocol_version" / Int8ub,
        "device_version" / Int8ub,
        "name_length" / Int8ub,
        "name" / Array(this.name_length, Byte),
        "description_length" / Int16ub,
        "description" / Array(this.description_length, Byte)
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.mac, self.syndesi_protocol_version, self.device_version, self.name_length, self.name, self.description_length, self.description = parsed_values.mac, parsed_values.syndesi_protocol_version, parsed_values.device_version, parsed_values.name_length, parsed_values.name, parsed_values.description_length, parsed_values.description
    def value(self):
        buffer = self.format.build(dict(mac = self.mac, syndesi_protocol_version = self.syndesi_protocol_version, device_version = self.device_version, name_length = self.name_length, name = self.name, description_length = self.description_length, description = self.description))
        return buffer
    
@dataclass
class REGISTER_READ_16_request(Payload):
    address : int = None
    command_ID = 0x0100
    format = Struct(
        "address" / Int16ub
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.address = parsed_values.address
    def value(self):
        buffer = self.format.build(dict(address = self.address))
        return buffer
    
@dataclass
class REGISTER_READ_16_reply(Payload):
    data : int = None
    command_ID = 0x0100
    format = Struct(
        "data" / Int16ub
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.data = parsed_values.data
    def value(self):
        buffer = self.format.build(dict(data = self.data))
        return buffer
    
@dataclass
class REGISTER_WRITE_16_request(Payload):
    addresss : int = None
    data : int = None
    command_ID = 0x0101
    format = Struct(
        "addresss" / Int16ub,
        "data" / Int16ub
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.addresss, self.data = parsed_values.addresss, parsed_values.data
    def value(self):
        buffer = self.format.build(dict(addresss = self.addresss, data = self.data))
        return buffer
    
@dataclass
class REGISTER_WRITE_16_reply(Payload):
    status : int = None
    command_ID = 0x0101
    format = Struct(
        "status" / Int16ub
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.status = parsed_values.status
    def value(self):
        buffer = self.format.build(dict(status = self.status))
        return buffer
    
@dataclass
class SPI_READ_WRITE_request(Payload):
    interface_index : int = None
    write_size : int = None
    write_data : bytearray = None
    command_ID = 0x0110
    format = Struct(
        "interface_index" / Int8ub,
        "write_size" / Int16ub,
        "write_data" / Array(this.write_size, Byte)
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.interface_index, self.write_size, self.write_data = parsed_values.interface_index, parsed_values.write_size, parsed_values.write_data
    def value(self):
        buffer = self.format.build(dict(interface_index = self.interface_index, write_size = self.write_size, write_data = self.write_data))
        return buffer
    
@dataclass
class SPI_READ_WRITE_reply(Payload):
    read_size : int = None
    read_data : bytearray = None
    command_ID = 0x0110
    format = Struct(
        "read_size" / Int16ub,
        "read_data" / Array(this.read_size, Byte)
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.read_size, self.read_data = parsed_values.read_size, parsed_values.read_data
    def value(self):
        buffer = self.format.build(dict(read_size = self.read_size, read_data = self.read_data))
        return buffer
    
@dataclass
class SPI_WRITE_ONLY_request(Payload):
    interface_index : int = None
    write_size : int = None
    write_data : bytearray = None
    command_ID = 0x0111
    format = Struct(
        "interface_index" / Int8ub,
        "write_size" / Int16ub,
        "write_data" / Array(this.write_size, Byte)
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.interface_index, self.write_size, self.write_data = parsed_values.interface_index, parsed_values.write_size, parsed_values.write_data
    def value(self):
        buffer = self.format.build(dict(interface_index = self.interface_index, write_size = self.write_size, write_data = self.write_data))
        return buffer
    
@dataclass
class SPI_WRITE_ONLY_reply(Payload):
    status : int = None
    command_ID = 0x0111
    format = Struct(
        "status" / Int16ub
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.status = parsed_values.status
    def value(self):
        buffer = self.format.build(dict(status = self.status))
        return buffer
    
@dataclass
class I2C_READ_request(Payload):
    interface_index : int = None
    read_size : int = None
    command_ID = 0x0120
    format = Struct(
        "interface_index" / Int8ub,
        "read_size" / Int16ub
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.interface_index, self.read_size = parsed_values.interface_index, parsed_values.read_size
    def value(self):
        buffer = self.format.build(dict(interface_index = self.interface_index, read_size = self.read_size))
        return buffer
    
@dataclass
class I2C_READ_reply(Payload):
    read_size : int = None
    read_data : bytearray = None
    command_ID = 0x0120
    format = Struct(
        "read_size" / Int16ub,
        "read_data" / Array(this.read_size, Byte)
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.read_size, self.read_data = parsed_values.read_size, parsed_values.read_data
    def value(self):
        buffer = self.format.build(dict(read_size = self.read_size, read_data = self.read_data))
        return buffer
    
@dataclass
class I2C_WRITE_request(Payload):
    interface_index : int = None
    write_size : int = None
    write_data : bytearray = None
    command_ID = 0x0121
    format = Struct(
        "interface_index" / Int8ub,
        "write_size" / Int16ub,
        "write_data" / Array(this.write_size, Byte)
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.interface_index, self.write_size, self.write_data = parsed_values.interface_index, parsed_values.write_size, parsed_values.write_data
    def value(self):
        buffer = self.format.build(dict(interface_index = self.interface_index, write_size = self.write_size, write_data = self.write_data))
        return buffer
    
@dataclass
class I2C_WRITE_reply(Payload):
    status : int = None
    command_ID = 0x0121
    format = Struct(
        "status" / Int16ub
    )
    def parse(self, buffer=None):
        """
        Create a payload instance from buffer
        """

        if not buffer is None:
            # Initialize variables with input buffer
            parsed_values = self.format.parse(buffer)
            self.status = parsed_values.status
    def value(self):
        buffer = self.format.build(dict(status = self.status))
        return buffer
    


class PayloadMatch(TypedDict):
    command: Commands
    payload : Payload

payload_match : PayloadMatch = {
    Commands_IDs.NO_COMMAND.value : NO_COMMAND_reply,
    Commands_IDs.DEVICE_DISCOVER.value : DEVICE_DISCOVER_reply,
    Commands_IDs.REGISTER_READ_16.value : REGISTER_READ_16_reply,
    Commands_IDs.REGISTER_WRITE_16.value : REGISTER_WRITE_16_reply,
    Commands_IDs.SPI_READ_WRITE.value : SPI_READ_WRITE_reply,
    Commands_IDs.SPI_WRITE_ONLY.value : SPI_WRITE_ONLY_reply,
    Commands_IDs.I2C_READ.value : I2C_READ_reply,
    Commands_IDs.I2C_WRITE.value : I2C_WRITE_reply,

}

class SpecialValues(Enum):
    NO_VALUE = 0x0000
    ACK = 0x0001
    NAK = 0x0002
    ERROR_FRAME_INVALID = 0x0003