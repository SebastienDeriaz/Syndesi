/* THIS FILE IS GENERATED AUTOMATICALLY
 *  DO NOT EDIT
 *  This file has been written by the script generate_commands.py
 *  date : 22-08-14 08:09:50
 */


#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

#include <vector>

#include "syndesi_tools.hpp"
#include "syndesi_types.hpp"


// true  : copy input buffer contents in each field array
// false : keep the data in the input buffer and reference through pointer
#define COPY_ARRAY_ARGUMENTS true

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
private:
    virtual void parse(const Buffer& buffer) = 0;
    virtual void build(Buffer buffer) = 0;
    virtual size_t payloadLength() = 0;
    virtual cmd_t getCommand() = 0;
    
    
public:
    // The fields are public (declared in the derived class)

    
    friend class Frame;
    friend class Payloads;
};


class ERROR : public Payload{
public:

    enum error_code_t {INVALID_FRAME, OTHER}error_code;

    ERROR() {};
    ERROR(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0001;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&error_code, 1);

    }

    size_t payloadLength() {
        return 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&error_code, payloadBuffer.data + pos, 1);

    }
};

class DEVICE_DISCOVER : public Payload{
public:



    DEVICE_DISCOVER() {};
    DEVICE_DISCOVER(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0002;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
#if COPY_ARRAY_ARGUMENTS
        memcpy(ID.data, payloadBuffer.data + pos, 20);
#else
        ID.data = payloadBuffer.data + pos;
#endif
        ID.length = 20;

    }

    size_t payloadLength() {
        return 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        memcpy(payloadBuffer.data + pos, ID.data, 20);

    }
};

class DEVICE_DISCOVER : public Payload{
public:

    uint8_t syndesi_protocol_version;

    DEVICE_DISCOVER() {};
    DEVICE_DISCOVER(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0002;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
#if COPY_ARRAY_ARGUMENTS
        memcpy(ID.data, payloadBuffer.data + pos, 20);
#else
        ID.data = payloadBuffer.data + pos;
#endif
        ID.length = 20;
        pos += ntoh(payloadBuffer.data + pos, (char*)&syndesi_protocol_version, 1);

    }

    size_t payloadLength() {
        return  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        memcpy(payloadBuffer.data + pos, ID.data, 20);
        pos += hton((char*)&syndesi_protocol_version, payloadBuffer.data + pos, 1);

    }
};

class DEVICE_DISCOVER : public Payload{
public:

    uint8_t syndesi_protocol_version;    uint8_t device_version;

    DEVICE_DISCOVER() {};
    DEVICE_DISCOVER(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0002;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
#if COPY_ARRAY_ARGUMENTS
        memcpy(ID.data, payloadBuffer.data + pos, 20);
#else
        ID.data = payloadBuffer.data + pos;
#endif
        ID.length = 20;
        pos += ntoh(payloadBuffer.data + pos, (char*)&syndesi_protocol_version, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&device_version, 1);

    }

    size_t payloadLength() {
        return  +  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        memcpy(payloadBuffer.data + pos, ID.data, 20);
        pos += hton((char*)&syndesi_protocol_version, payloadBuffer.data + pos, 1);
        pos += hton((char*)&device_version, payloadBuffer.data + pos, 1);

    }
};

class DEVICE_DISCOVER : public Payload{
public:

    uint8_t syndesi_protocol_version;    uint8_t device_version;    uint8_t name_length;

    DEVICE_DISCOVER() {};
    DEVICE_DISCOVER(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0002;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
#if COPY_ARRAY_ARGUMENTS
        memcpy(ID.data, payloadBuffer.data + pos, 20);
#else
        ID.data = payloadBuffer.data + pos;
#endif
        ID.length = 20;
        pos += ntoh(payloadBuffer.data + pos, (char*)&syndesi_protocol_version, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&device_version, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&name_length, 1);

    }

    size_t payloadLength() {
        return  +  +  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        memcpy(payloadBuffer.data + pos, ID.data, 20);
        pos += hton((char*)&syndesi_protocol_version, payloadBuffer.data + pos, 1);
        pos += hton((char*)&device_version, payloadBuffer.data + pos, 1);
        pos += hton((char*)&name_length, payloadBuffer.data + pos, 1);

    }
};

class DEVICE_DISCOVER : public Payload{
public:

    uint8_t syndesi_protocol_version;    uint8_t device_version;    uint8_t name_length;

    DEVICE_DISCOVER() {};
    DEVICE_DISCOVER(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0002;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
#if COPY_ARRAY_ARGUMENTS
        memcpy(ID.data, payloadBuffer.data + pos, 20);
#else
        ID.data = payloadBuffer.data + pos;
#endif
        ID.length = 20;
        pos += ntoh(payloadBuffer.data + pos, (char*)&syndesi_protocol_version, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&device_version, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&name_length, 1);
#if COPY_ARRAY_ARGUMENTS
        memcpy(name.data, payloadBuffer.data + pos, name_length);
#else
        name.data = payloadBuffer.data + pos;
#endif
        name.length = name_length;

    }

    size_t payloadLength() {
        return  +  +  +  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        memcpy(payloadBuffer.data + pos, ID.data, 20);
        pos += hton((char*)&syndesi_protocol_version, payloadBuffer.data + pos, 1);
        pos += hton((char*)&device_version, payloadBuffer.data + pos, 1);
        pos += hton((char*)&name_length, payloadBuffer.data + pos, 1);
        memcpy(payloadBuffer.data + pos, name.data, name_length);

    }
};

class DEVICE_DISCOVER : public Payload{
public:

    uint8_t syndesi_protocol_version;    uint8_t device_version;    uint8_t name_length;    uint16_t description_length;

    DEVICE_DISCOVER() {};
    DEVICE_DISCOVER(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0002;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
#if COPY_ARRAY_ARGUMENTS
        memcpy(ID.data, payloadBuffer.data + pos, 20);
#else
        ID.data = payloadBuffer.data + pos;
#endif
        ID.length = 20;
        pos += ntoh(payloadBuffer.data + pos, (char*)&syndesi_protocol_version, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&device_version, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&name_length, 1);
#if COPY_ARRAY_ARGUMENTS
        memcpy(name.data, payloadBuffer.data + pos, name_length);
#else
        name.data = payloadBuffer.data + pos;
#endif
        name.length = name_length;
        pos += ntoh(payloadBuffer.data + pos, (char*)&description_length, 2);

    }

    size_t payloadLength() {
        return  +  +  +  +  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        memcpy(payloadBuffer.data + pos, ID.data, 20);
        pos += hton((char*)&syndesi_protocol_version, payloadBuffer.data + pos, 1);
        pos += hton((char*)&device_version, payloadBuffer.data + pos, 1);
        pos += hton((char*)&name_length, payloadBuffer.data + pos, 1);
        memcpy(payloadBuffer.data + pos, name.data, name_length);
        pos += hton((char*)&description_length, payloadBuffer.data + pos, 2);

    }
};

class DEVICE_DISCOVER : public Payload{
public:

    uint8_t syndesi_protocol_version;    uint8_t device_version;    uint8_t name_length;    uint16_t description_length;

    DEVICE_DISCOVER() {};
    DEVICE_DISCOVER(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0002;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
#if COPY_ARRAY_ARGUMENTS
        memcpy(ID.data, payloadBuffer.data + pos, 20);
#else
        ID.data = payloadBuffer.data + pos;
#endif
        ID.length = 20;
        pos += ntoh(payloadBuffer.data + pos, (char*)&syndesi_protocol_version, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&device_version, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&name_length, 1);
#if COPY_ARRAY_ARGUMENTS
        memcpy(name.data, payloadBuffer.data + pos, name_length);
#else
        name.data = payloadBuffer.data + pos;
#endif
        name.length = name_length;
        pos += ntoh(payloadBuffer.data + pos, (char*)&description_length, 2);
#if COPY_ARRAY_ARGUMENTS
        memcpy(description.data, payloadBuffer.data + pos, description_length);
#else
        description.data = payloadBuffer.data + pos;
#endif
        description.length = description_length;

    }

    size_t payloadLength() {
        return  +  +  +  +  +  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        memcpy(payloadBuffer.data + pos, ID.data, 20);
        pos += hton((char*)&syndesi_protocol_version, payloadBuffer.data + pos, 1);
        pos += hton((char*)&device_version, payloadBuffer.data + pos, 1);
        pos += hton((char*)&name_length, payloadBuffer.data + pos, 1);
        memcpy(payloadBuffer.data + pos, name.data, name_length);
        pos += hton((char*)&description_length, payloadBuffer.data + pos, 2);
        memcpy(payloadBuffer.data + pos, description.data, description_length);

    }
};

class REGISTER_READ_16 : public Payload{
public:

    uint16_t address;

    REGISTER_READ_16() {};
    REGISTER_READ_16(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0100;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&address, 2);

    }

    size_t payloadLength() {
        return 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&address, payloadBuffer.data + pos, 2);

    }
};

class REGISTER_READ_16 : public Payload{
public:

    uint16_t address;    uint16_t data;

    REGISTER_READ_16() {};
    REGISTER_READ_16(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0100;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&address, 2);
        pos += ntoh(payloadBuffer.data + pos, (char*)&data, 2);

    }

    size_t payloadLength() {
        return 2
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&address, payloadBuffer.data + pos, 2);
        pos += hton((char*)&data, payloadBuffer.data + pos, 2);

    }
};

class REGISTER_WRITE_16 : public Payload{
public:

    uint16_t addresss;

    REGISTER_WRITE_16() {};
    REGISTER_WRITE_16(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0101;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&addresss, 2);

    }

    size_t payloadLength() {
        return 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&addresss, payloadBuffer.data + pos, 2);

    }
};

class REGISTER_WRITE_16 : public Payload{
public:

    uint16_t addresss;    uint16_t data;

    REGISTER_WRITE_16() {};
    REGISTER_WRITE_16(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0101;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&addresss, 2);
        pos += ntoh(payloadBuffer.data + pos, (char*)&data, 2);

    }

    size_t payloadLength() {
        return  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&addresss, payloadBuffer.data + pos, 2);
        pos += hton((char*)&data, payloadBuffer.data + pos, 2);

    }
};

class REGISTER_WRITE_16 : public Payload{
public:

    uint16_t addresss;    uint16_t data;    enum status_t {OK, NOK}status;

    REGISTER_WRITE_16() {};
    REGISTER_WRITE_16(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0101;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&addresss, 2);
        pos += ntoh(payloadBuffer.data + pos, (char*)&data, 2);
        pos += ntoh(payloadBuffer.data + pos, (char*)&status, 1);

    }

    size_t payloadLength() {
        return  + 2
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&addresss, payloadBuffer.data + pos, 2);
        pos += hton((char*)&data, payloadBuffer.data + pos, 2);
        pos += hton((char*)&status, payloadBuffer.data + pos, 1);

    }
};

class SPI_READ_WRITE : public Payload{
public:

    uint8_t interface_index;

    SPI_READ_WRITE() {};
    SPI_READ_WRITE(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0110;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);

    }

    size_t payloadLength() {
        return 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);

    }
};

class SPI_READ_WRITE : public Payload{
public:

    uint8_t interface_index;    uint16_t write_size;

    SPI_READ_WRITE() {};
    SPI_READ_WRITE(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0110;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&write_size, 2);

    }

    size_t payloadLength() {
        return  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&write_size, payloadBuffer.data + pos, 2);

    }
};

class SPI_READ_WRITE : public Payload{
public:

    uint8_t interface_index;    uint16_t write_size;

    SPI_READ_WRITE() {};
    SPI_READ_WRITE(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0110;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&write_size, 2);
#if COPY_ARRAY_ARGUMENTS
        memcpy(write_data.data, payloadBuffer.data + pos, write_size);
#else
        write_data.data = payloadBuffer.data + pos;
#endif
        write_data.length = write_size;

    }

    size_t payloadLength() {
        return  +  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&write_size, payloadBuffer.data + pos, 2);
        memcpy(payloadBuffer.data + pos, write_data.data, write_size);

    }
};

class SPI_READ_WRITE : public Payload{
public:

    uint8_t interface_index;    uint16_t write_size;    uint16_t read_size;

    SPI_READ_WRITE() {};
    SPI_READ_WRITE(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0110;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&write_size, 2);
#if COPY_ARRAY_ARGUMENTS
        memcpy(write_data.data, payloadBuffer.data + pos, write_size);
#else
        write_data.data = payloadBuffer.data + pos;
#endif
        write_data.length = write_size;
        pos += ntoh(payloadBuffer.data + pos, (char*)&read_size, 2);

    }

    size_t payloadLength() {
        return  +  + write_size
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&write_size, payloadBuffer.data + pos, 2);
        memcpy(payloadBuffer.data + pos, write_data.data, write_size);
        pos += hton((char*)&read_size, payloadBuffer.data + pos, 2);

    }
};

class SPI_READ_WRITE : public Payload{
public:

    uint8_t interface_index;    uint16_t write_size;    uint16_t read_size;

    SPI_READ_WRITE() {};
    SPI_READ_WRITE(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0110;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&write_size, 2);
#if COPY_ARRAY_ARGUMENTS
        memcpy(write_data.data, payloadBuffer.data + pos, write_size);
#else
        write_data.data = payloadBuffer.data + pos;
#endif
        write_data.length = write_size;
        pos += ntoh(payloadBuffer.data + pos, (char*)&read_size, 2);
#if COPY_ARRAY_ARGUMENTS
        memcpy(read_data.data, payloadBuffer.data + pos, read_size);
#else
        read_data.data = payloadBuffer.data + pos;
#endif
        read_data.length = read_size;

    }

    size_t payloadLength() {
        return  +  + write_size + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&write_size, payloadBuffer.data + pos, 2);
        memcpy(payloadBuffer.data + pos, write_data.data, write_size);
        pos += hton((char*)&read_size, payloadBuffer.data + pos, 2);
        memcpy(payloadBuffer.data + pos, read_data.data, read_size);

    }
};

class SPI_WRITE_ONLY : public Payload{
public:

    uint8_t interface_index;

    SPI_WRITE_ONLY() {};
    SPI_WRITE_ONLY(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0111;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);

    }

    size_t payloadLength() {
        return 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);

    }
};

class SPI_WRITE_ONLY : public Payload{
public:

    uint8_t interface_index;    uint16_t write_size;

    SPI_WRITE_ONLY() {};
    SPI_WRITE_ONLY(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0111;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&write_size, 2);

    }

    size_t payloadLength() {
        return  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&write_size, payloadBuffer.data + pos, 2);

    }
};

class SPI_WRITE_ONLY : public Payload{
public:

    uint8_t interface_index;    uint16_t write_size;

    SPI_WRITE_ONLY() {};
    SPI_WRITE_ONLY(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0111;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&write_size, 2);
#if COPY_ARRAY_ARGUMENTS
        memcpy(write_data.data, payloadBuffer.data + pos, write_size);
#else
        write_data.data = payloadBuffer.data + pos;
#endif
        write_data.length = write_size;

    }

    size_t payloadLength() {
        return  +  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&write_size, payloadBuffer.data + pos, 2);
        memcpy(payloadBuffer.data + pos, write_data.data, write_size);

    }
};

class SPI_WRITE_ONLY : public Payload{
public:

    uint8_t interface_index;    uint16_t write_size;    enum status_t {OK, NOK}status;

    SPI_WRITE_ONLY() {};
    SPI_WRITE_ONLY(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0111;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&write_size, 2);
#if COPY_ARRAY_ARGUMENTS
        memcpy(write_data.data, payloadBuffer.data + pos, write_size);
#else
        write_data.data = payloadBuffer.data + pos;
#endif
        write_data.length = write_size;
        pos += ntoh(payloadBuffer.data + pos, (char*)&status, 1);

    }

    size_t payloadLength() {
        return  +  + write_size
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&write_size, payloadBuffer.data + pos, 2);
        memcpy(payloadBuffer.data + pos, write_data.data, write_size);
        pos += hton((char*)&status, payloadBuffer.data + pos, 1);

    }
};

class I2C_READ : public Payload{
public:

    uint8_t interface_index;

    I2C_READ() {};
    I2C_READ(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0120;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);

    }

    size_t payloadLength() {
        return 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);

    }
};

class I2C_READ : public Payload{
public:

    uint8_t interface_index;    uint16_t read_size;

    I2C_READ() {};
    I2C_READ(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0120;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&read_size, 2);

    }

    size_t payloadLength() {
        return  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&read_size, payloadBuffer.data + pos, 2);

    }
};

class I2C_READ : public Payload{
public:

    uint8_t interface_index;    uint16_t read_size;    uint16_t read_size;

    I2C_READ() {};
    I2C_READ(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0120;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&read_size, 2);
        pos += ntoh(payloadBuffer.data + pos, (char*)&read_size, 2);

    }

    size_t payloadLength() {
        return  + 2
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&read_size, payloadBuffer.data + pos, 2);
        pos += hton((char*)&read_size, payloadBuffer.data + pos, 2);

    }
};

class I2C_READ : public Payload{
public:

    uint8_t interface_index;    uint16_t read_size;    uint16_t read_size;

    I2C_READ() {};
    I2C_READ(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0120;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&read_size, 2);
        pos += ntoh(payloadBuffer.data + pos, (char*)&read_size, 2);
#if COPY_ARRAY_ARGUMENTS
        memcpy(read_data.data, payloadBuffer.data + pos, read_size);
#else
        read_data.data = payloadBuffer.data + pos;
#endif
        read_data.length = read_size;

    }

    size_t payloadLength() {
        return  + 2 + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&read_size, payloadBuffer.data + pos, 2);
        pos += hton((char*)&read_size, payloadBuffer.data + pos, 2);
        memcpy(payloadBuffer.data + pos, read_data.data, read_size);

    }
};

class I2C_WRITE : public Payload{
public:

    uint8_t interface_index;

    I2C_WRITE() {};
    I2C_WRITE(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0121;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);

    }

    size_t payloadLength() {
        return 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);

    }
};

class I2C_WRITE : public Payload{
public:

    uint8_t interface_index;    uint16_t write_size;

    I2C_WRITE() {};
    I2C_WRITE(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0121;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&write_size, 2);

    }

    size_t payloadLength() {
        return  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&write_size, payloadBuffer.data + pos, 2);

    }
};

class I2C_WRITE : public Payload{
public:

    uint8_t interface_index;    uint16_t write_size;

    I2C_WRITE() {};
    I2C_WRITE(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0121;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&write_size, 2);
#if COPY_ARRAY_ARGUMENTS
        memcpy(write_data.data, payloadBuffer.data + pos, write_size);
#else
        write_data.data = payloadBuffer.data + pos;
#endif
        write_data.length = write_size;

    }

    size_t payloadLength() {
        return  +  + 
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&write_size, payloadBuffer.data + pos, 2);
        memcpy(payloadBuffer.data + pos, write_data.data, write_size);

    }
};

class I2C_WRITE : public Payload{
public:

    uint8_t interface_index;    uint16_t write_size;    enum status_t {OK, NOK}status;

    I2C_WRITE() {};
    I2C_WRITE(const Buffer& buffer) {parse(buffer);};
private:

    cmd_t getCommand() {return 0x0121;}    


    void parse(const Buffer& payloadBuffer) {
        size_t pos = 0;
        pos += ntoh(payloadBuffer.data + pos, (char*)&interface_index, 1);
        pos += ntoh(payloadBuffer.data + pos, (char*)&write_size, 2);
#if COPY_ARRAY_ARGUMENTS
        memcpy(write_data.data, payloadBuffer.data + pos, write_size);
#else
        write_data.data = payloadBuffer.data + pos;
#endif
        write_data.length = write_size;
        pos += ntoh(payloadBuffer.data + pos, (char*)&status, 1);

    }

    size_t payloadLength() {
        return  +  + write_size
    }

    void build(Buffer payloadBuffer) {
        size_t pos = 0;
        pos += hton((char*)&interface_index, payloadBuffer.data + pos, 1);
        pos += hton((char*)&write_size, payloadBuffer.data + pos, 2);
        memcpy(payloadBuffer.data + pos, write_data.data, write_size);
        pos += hton((char*)&status, payloadBuffer.data + pos, 1);

    }
};



}  // namespace syndesi

#endif  // COMMANDS_H