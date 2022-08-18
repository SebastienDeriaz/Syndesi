/* THIS FILE IS GENERATED AUTOMATICALLY
 *  DO NOT EDIT
 *  This file has been written by the script generate_commands.py
 *  date : 22-08-18 12:56:32
 */


#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

#include <vector>

#include "syndesi_tools.hpp"
#include "syndesi_types.hpp"
#include "buffer.hpp"
#include <memory>

namespace syndesi {

enum commands : cmd_t {
    NO_COMMAND = 0x0000,
    ERROR = 0x0001,
    DEVICE_DISCOVER = 0x0002,
    REGISTER_READ_16 = 0x0100,
    REGISTER_WRITE_16 = 0x0101,
    SPI_READ_WRITE = 0x0110,
    SPI_WRITE_ONLY = 0x0111,
    I2C_READ = 0x0120,
    I2C_WRITE = 0x0121
};

class Payload {
   public:
    virtual void build(Buffer* buffer) = 0;
    virtual size_t payloadLength() = 0;
    virtual cmd_t getCommand() = 0;
};






class ERROR_reply : public Payload{
public:

    enum error_code_t {INVALID_FRAME, OTHER}error_code;


    ERROR_reply() {};
    ERROR_reply(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&error_code), 1);

    };
private:

    cmd_t getCommand() {return 0x0001;}    



    size_t payloadLength() {
        return 1;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&error_code), payloadBuffer->data() + pos, 1);

    }
};

class DEVICE_DISCOVER_request : public Payload{
public:



    DEVICE_DISCOVER_request() {};
    DEVICE_DISCOVER_request(Buffer* payloadBuffer) {
        size_t pos = 0;
        
    };
private:

    cmd_t getCommand() {return 0x0002;}    



    size_t payloadLength() {
        return 0;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;

    }
};

class DEVICE_DISCOVER_reply : public Payload{
public:

    Buffer ID;
    uint8_t syndesi_protocol_version;
    uint8_t device_version;
    uint8_t name_length;
    Buffer name;
    uint16_t description_length;
    Buffer description;


    DEVICE_DISCOVER_reply() {};
    DEVICE_DISCOVER_reply(Buffer* payloadBuffer) {
        size_t pos = 0;
                ID.fromParent(payloadBuffer, pos, 20);        pos += 20;        pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&syndesi_protocol_version), 1);
        pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&device_version), 1);
        pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&name_length), 1);
        name.fromParent(payloadBuffer, pos, name_length);        pos += name_length;        pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&description_length), 2);
        description.fromParent(payloadBuffer, pos, description_length);        pos += description_length;
    };
private:

    cmd_t getCommand() {return 0x0002;}    



    size_t payloadLength() {
        return 20 + 1 + 1 + 1 + name_length + 2 + description_length;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&syndesi_protocol_version), payloadBuffer->data() + pos, 1);
        pos += hton(reinterpret_cast<byte*>(&device_version), payloadBuffer->data() + pos, 1);
        pos += hton(reinterpret_cast<byte*>(&name_length), payloadBuffer->data() + pos, 1);
        pos += hton(reinterpret_cast<byte*>(&description_length), payloadBuffer->data() + pos, 2);

    }
};

class REGISTER_READ_16_request : public Payload{
public:

    uint16_t address;


    REGISTER_READ_16_request() {};
    REGISTER_READ_16_request(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&address), 2);

    };
private:

    cmd_t getCommand() {return 0x0100;}    



    size_t payloadLength() {
        return 2;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&address), payloadBuffer->data() + pos, 2);

    }
};

class REGISTER_READ_16_reply : public Payload{
public:

    uint16_t data;


    REGISTER_READ_16_reply() {};
    REGISTER_READ_16_reply(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&data), 2);

    };
private:

    cmd_t getCommand() {return 0x0100;}    



    size_t payloadLength() {
        return 2;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&data), payloadBuffer->data() + pos, 2);

    }
};

class REGISTER_WRITE_16_request : public Payload{
public:

    uint16_t addresss;
    uint16_t data;


    REGISTER_WRITE_16_request() {};
    REGISTER_WRITE_16_request(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&addresss), 2);
        pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&data), 2);

    };
private:

    cmd_t getCommand() {return 0x0101;}    



    size_t payloadLength() {
        return 2 + 2;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&addresss), payloadBuffer->data() + pos, 2);
        pos += hton(reinterpret_cast<byte*>(&data), payloadBuffer->data() + pos, 2);

    }
};

class REGISTER_WRITE_16_reply : public Payload{
public:

    enum status_t {OK, NOK}status;


    REGISTER_WRITE_16_reply() {};
    REGISTER_WRITE_16_reply(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&status), 1);

    };
private:

    cmd_t getCommand() {return 0x0101;}    



    size_t payloadLength() {
        return 1;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&status), payloadBuffer->data() + pos, 1);

    }
};

class SPI_READ_WRITE_request : public Payload{
public:

    uint8_t interface_index;
    uint16_t write_size;
    Buffer write_data;


    SPI_READ_WRITE_request() {};
    SPI_READ_WRITE_request(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&interface_index), 1);
        pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&write_size), 2);
        write_data.fromParent(payloadBuffer, pos, write_size);        pos += write_size;
    };
private:

    cmd_t getCommand() {return 0x0110;}    



    size_t payloadLength() {
        return 1 + 2 + write_size;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&interface_index), payloadBuffer->data() + pos, 1);
        pos += hton(reinterpret_cast<byte*>(&write_size), payloadBuffer->data() + pos, 2);

    }
};

class SPI_READ_WRITE_reply : public Payload{
public:

    uint16_t read_size;
    Buffer read_data;


    SPI_READ_WRITE_reply() {};
    SPI_READ_WRITE_reply(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&read_size), 2);
        read_data.fromParent(payloadBuffer, pos, read_size);        pos += read_size;
    };
private:

    cmd_t getCommand() {return 0x0110;}    



    size_t payloadLength() {
        return 2 + read_size;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&read_size), payloadBuffer->data() + pos, 2);

    }
};

class SPI_WRITE_ONLY_request : public Payload{
public:

    uint8_t interface_index;
    uint16_t write_size;
    Buffer write_data;


    SPI_WRITE_ONLY_request() {};
    SPI_WRITE_ONLY_request(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&interface_index), 1);
        pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&write_size), 2);
        write_data.fromParent(payloadBuffer, pos, write_size);        pos += write_size;
    };
private:

    cmd_t getCommand() {return 0x0111;}    



    size_t payloadLength() {
        return 1 + 2 + write_size;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&interface_index), payloadBuffer->data() + pos, 1);
        pos += hton(reinterpret_cast<byte*>(&write_size), payloadBuffer->data() + pos, 2);

    }
};

class SPI_WRITE_ONLY_reply : public Payload{
public:

    enum status_t {OK, NOK}status;


    SPI_WRITE_ONLY_reply() {};
    SPI_WRITE_ONLY_reply(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&status), 1);

    };
private:

    cmd_t getCommand() {return 0x0111;}    



    size_t payloadLength() {
        return 1;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&status), payloadBuffer->data() + pos, 1);

    }
};

class I2C_READ_request : public Payload{
public:

    uint8_t interface_index;
    uint16_t read_size;


    I2C_READ_request() {};
    I2C_READ_request(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&interface_index), 1);
        pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&read_size), 2);

    };
private:

    cmd_t getCommand() {return 0x0120;}    



    size_t payloadLength() {
        return 1 + 2;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&interface_index), payloadBuffer->data() + pos, 1);
        pos += hton(reinterpret_cast<byte*>(&read_size), payloadBuffer->data() + pos, 2);

    }
};

class I2C_READ_reply : public Payload{
public:

    uint16_t read_size;
    Buffer read_data;


    I2C_READ_reply() {};
    I2C_READ_reply(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&read_size), 2);
        read_data.fromParent(payloadBuffer, pos, read_size);        pos += read_size;
    };
private:

    cmd_t getCommand() {return 0x0120;}    



    size_t payloadLength() {
        return 2 + read_size;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&read_size), payloadBuffer->data() + pos, 2);

    }
};

class I2C_WRITE_request : public Payload{
public:

    uint8_t interface_index;
    uint16_t write_size;
    Buffer write_data;


    I2C_WRITE_request() {};
    I2C_WRITE_request(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&interface_index), 1);
        pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&write_size), 2);
        write_data.fromParent(payloadBuffer, pos, write_size);        pos += write_size;
    };
private:

    cmd_t getCommand() {return 0x0121;}    



    size_t payloadLength() {
        return 1 + 2 + write_size;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&interface_index), payloadBuffer->data() + pos, 1);
        pos += hton(reinterpret_cast<byte*>(&write_size), payloadBuffer->data() + pos, 2);

    }
};

class I2C_WRITE_reply : public Payload{
public:

    enum status_t {OK, NOK}status;


    I2C_WRITE_reply() {};
    I2C_WRITE_reply(Buffer* payloadBuffer) {
        size_t pos = 0;
                pos += ntoh(payloadBuffer->data() + pos, reinterpret_cast<byte*>(&status), 1);

    };
private:

    cmd_t getCommand() {return 0x0121;}    



    size_t payloadLength() {
        return 1;
    }

    void build(Buffer* payloadBuffer) {
        size_t pos = 0;
        pos += hton(reinterpret_cast<byte*>(&status), payloadBuffer->data() + pos, 1);

    }
};



}  // namespace syndesi

#endif  // COMMANDS_H