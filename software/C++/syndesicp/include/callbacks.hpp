/* THIS FILE IS GENERATED AUTOMATICALLY
 *  DO NOT EDIT
 *  This file has been written by the script generate_commands.py
 *  date : 22-08-14 08:09:50
 */

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "syndesi_types.hpp"
#include "payloads.hpp"
#include "callbacks_configuration.hpp"

namespace syndesi {

class Callbacks {
    public:
        void processRequest(cmd_t command, Buffer& payloadBuffer);
        void processReply(cmd_t command, Buffer& payloadBuffer);

#ifdef USE_Command ERROR
        request : no
          reply : yes
   reply fields : [error_code(1/enum)]_REPLY_CALLBACK
    void Command ERROR
        request : no
          reply : yes
   reply fields : [error_code(1/enum)]_reply_callback(Command ERROR
        request : no
          reply : yes
   reply fields : [error_code(1/enum)]_reply& reply);
#endif
#ifdef USE_Command DEVICE_DISCOVER
        request : yes
          reply : yes
 request fields : []
   reply fields : [ID(20/char), syndesi_protocol_version(1/uint), device_version(1/uint), name_length(1/uint), name(name_length/char), description_length(2/uint), description(description_length/char)]_REQUEST_CALLBACK
    void Command DEVICE_DISCOVER
        request : yes
          reply : yes
 request fields : []
   reply fields : [ID(20/char), syndesi_protocol_version(1/uint), device_version(1/uint), name_length(1/uint), name(name_length/char), description_length(2/uint), description(description_length/char)]_request_callback(Command DEVICE_DISCOVER
        request : yes
          reply : yes
 request fields : []
   reply fields : [ID(20/char), syndesi_protocol_version(1/uint), device_version(1/uint), name_length(1/uint), name(name_length/char), description_length(2/uint), description(description_length/char)]_request& request, Command DEVICE_DISCOVER
        request : yes
          reply : yes
 request fields : []
   reply fields : [ID(20/char), syndesi_protocol_version(1/uint), device_version(1/uint), name_length(1/uint), name(name_length/char), description_length(2/uint), description(description_length/char)]_reply& reply);
#endif
#ifdef USE_Command DEVICE_DISCOVER
        request : yes
          reply : yes
 request fields : []
   reply fields : [ID(20/char), syndesi_protocol_version(1/uint), device_version(1/uint), name_length(1/uint), name(name_length/char), description_length(2/uint), description(description_length/char)]_REPLY_CALLBACK
    void Command DEVICE_DISCOVER
        request : yes
          reply : yes
 request fields : []
   reply fields : [ID(20/char), syndesi_protocol_version(1/uint), device_version(1/uint), name_length(1/uint), name(name_length/char), description_length(2/uint), description(description_length/char)]_reply_callback(Command DEVICE_DISCOVER
        request : yes
          reply : yes
 request fields : []
   reply fields : [ID(20/char), syndesi_protocol_version(1/uint), device_version(1/uint), name_length(1/uint), name(name_length/char), description_length(2/uint), description(description_length/char)]_reply& reply);
#endif
#ifdef USE_Command REGISTER_READ_16
        request : yes
          reply : yes
 request fields : [address(2/uint)]
   reply fields : [data(2/uint)]_REQUEST_CALLBACK
    void Command REGISTER_READ_16
        request : yes
          reply : yes
 request fields : [address(2/uint)]
   reply fields : [data(2/uint)]_request_callback(Command REGISTER_READ_16
        request : yes
          reply : yes
 request fields : [address(2/uint)]
   reply fields : [data(2/uint)]_request& request, Command REGISTER_READ_16
        request : yes
          reply : yes
 request fields : [address(2/uint)]
   reply fields : [data(2/uint)]_reply& reply);
#endif
#ifdef USE_Command REGISTER_READ_16
        request : yes
          reply : yes
 request fields : [address(2/uint)]
   reply fields : [data(2/uint)]_REPLY_CALLBACK
    void Command REGISTER_READ_16
        request : yes
          reply : yes
 request fields : [address(2/uint)]
   reply fields : [data(2/uint)]_reply_callback(Command REGISTER_READ_16
        request : yes
          reply : yes
 request fields : [address(2/uint)]
   reply fields : [data(2/uint)]_reply& reply);
#endif
#ifdef USE_Command REGISTER_WRITE_16
        request : yes
          reply : yes
 request fields : [addresss(2/uint), data(2/uint)]
   reply fields : [status(1/enum)]_REQUEST_CALLBACK
    void Command REGISTER_WRITE_16
        request : yes
          reply : yes
 request fields : [addresss(2/uint), data(2/uint)]
   reply fields : [status(1/enum)]_request_callback(Command REGISTER_WRITE_16
        request : yes
          reply : yes
 request fields : [addresss(2/uint), data(2/uint)]
   reply fields : [status(1/enum)]_request& request, Command REGISTER_WRITE_16
        request : yes
          reply : yes
 request fields : [addresss(2/uint), data(2/uint)]
   reply fields : [status(1/enum)]_reply& reply);
#endif
#ifdef USE_Command REGISTER_WRITE_16
        request : yes
          reply : yes
 request fields : [addresss(2/uint), data(2/uint)]
   reply fields : [status(1/enum)]_REPLY_CALLBACK
    void Command REGISTER_WRITE_16
        request : yes
          reply : yes
 request fields : [addresss(2/uint), data(2/uint)]
   reply fields : [status(1/enum)]_reply_callback(Command REGISTER_WRITE_16
        request : yes
          reply : yes
 request fields : [addresss(2/uint), data(2/uint)]
   reply fields : [status(1/enum)]_reply& reply);
#endif
#ifdef USE_Command SPI_READ_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_REQUEST_CALLBACK
    void Command SPI_READ_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_request_callback(Command SPI_READ_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_request& request, Command SPI_READ_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_reply& reply);
#endif
#ifdef USE_Command SPI_READ_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_REPLY_CALLBACK
    void Command SPI_READ_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_reply_callback(Command SPI_READ_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_reply& reply);
#endif
#ifdef USE_Command SPI_WRITE_ONLY
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_REQUEST_CALLBACK
    void Command SPI_WRITE_ONLY
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_request_callback(Command SPI_WRITE_ONLY
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_request& request, Command SPI_WRITE_ONLY
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_reply& reply);
#endif
#ifdef USE_Command SPI_WRITE_ONLY
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_REPLY_CALLBACK
    void Command SPI_WRITE_ONLY
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_reply_callback(Command SPI_WRITE_ONLY
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_reply& reply);
#endif
#ifdef USE_Command I2C_READ
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), read_size(2/uint)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_REQUEST_CALLBACK
    void Command I2C_READ
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), read_size(2/uint)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_request_callback(Command I2C_READ
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), read_size(2/uint)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_request& request, Command I2C_READ
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), read_size(2/uint)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_reply& reply);
#endif
#ifdef USE_Command I2C_READ
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), read_size(2/uint)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_REPLY_CALLBACK
    void Command I2C_READ
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), read_size(2/uint)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_reply_callback(Command I2C_READ
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), read_size(2/uint)]
   reply fields : [read_size(2/uint), read_data(read_size/char)]_reply& reply);
#endif
#ifdef USE_Command I2C_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_REQUEST_CALLBACK
    void Command I2C_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_request_callback(Command I2C_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_request& request, Command I2C_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_reply& reply);
#endif
#ifdef USE_Command I2C_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_REPLY_CALLBACK
    void Command I2C_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_reply_callback(Command I2C_WRITE
        request : yes
          reply : yes
 request fields : [interface_index(1/uint), write_size(2/uint), write_data(write_size/char)]
   reply fields : [status(1/enum)]_reply& reply);
#endif


};

extern Callbacks callbacks;

}

#endif // CALLBACKS_H