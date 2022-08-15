/* THIS FILE IS GENERATED AUTOMATICALLY
 *  DO NOT EDIT
 *  This file has been written by the script generate_commands.py
 *  date : 22-08-15 16:39:29
 */

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "syndesi_types.hpp"
#include "payloads.hpp"
#include "callbacks_configuration.hpp"

namespace syndesi {

class Callbacks {
    public:
        Buffer processRequest(cmd_t command, Buffer& payloadBuffer);
        void processReply(cmd_t command, Buffer& payloadBuffer);

#ifdef USE_ERROR_REPLY_CALLBACK
    void ERROR_reply_callback(ERROR_reply& reply);
#endif
#ifdef USE_DEVICE_DISCOVER_REQUEST_CALLBACK
    void DEVICE_DISCOVER_request_callback(DEVICE_DISCOVER_request& request, DEVICE_DISCOVER_reply& reply);
#endif
#ifdef USE_DEVICE_DISCOVER_REPLY_CALLBACK
    void DEVICE_DISCOVER_reply_callback(DEVICE_DISCOVER_reply& reply);
#endif
#ifdef USE_REGISTER_READ_16_REQUEST_CALLBACK
    void REGISTER_READ_16_request_callback(REGISTER_READ_16_request& request, REGISTER_READ_16_reply& reply);
#endif
#ifdef USE_REGISTER_READ_16_REPLY_CALLBACK
    void REGISTER_READ_16_reply_callback(REGISTER_READ_16_reply& reply);
#endif
#ifdef USE_REGISTER_WRITE_16_REQUEST_CALLBACK
    void REGISTER_WRITE_16_request_callback(REGISTER_WRITE_16_request& request, REGISTER_WRITE_16_reply& reply);
#endif
#ifdef USE_REGISTER_WRITE_16_REPLY_CALLBACK
    void REGISTER_WRITE_16_reply_callback(REGISTER_WRITE_16_reply& reply);
#endif
#ifdef USE_SPI_READ_WRITE_REQUEST_CALLBACK
    void SPI_READ_WRITE_request_callback(SPI_READ_WRITE_request& request, SPI_READ_WRITE_reply& reply);
#endif
#ifdef USE_SPI_READ_WRITE_REPLY_CALLBACK
    void SPI_READ_WRITE_reply_callback(SPI_READ_WRITE_reply& reply);
#endif
#ifdef USE_SPI_WRITE_ONLY_REQUEST_CALLBACK
    void SPI_WRITE_ONLY_request_callback(SPI_WRITE_ONLY_request& request, SPI_WRITE_ONLY_reply& reply);
#endif
#ifdef USE_SPI_WRITE_ONLY_REPLY_CALLBACK
    void SPI_WRITE_ONLY_reply_callback(SPI_WRITE_ONLY_reply& reply);
#endif
#ifdef USE_I2C_READ_REQUEST_CALLBACK
    void I2C_READ_request_callback(I2C_READ_request& request, I2C_READ_reply& reply);
#endif
#ifdef USE_I2C_READ_REPLY_CALLBACK
    void I2C_READ_reply_callback(I2C_READ_reply& reply);
#endif
#ifdef USE_I2C_WRITE_REQUEST_CALLBACK
    void I2C_WRITE_request_callback(I2C_WRITE_request& request, I2C_WRITE_reply& reply);
#endif
#ifdef USE_I2C_WRITE_REPLY_CALLBACK
    void I2C_WRITE_reply_callback(I2C_WRITE_reply& reply);
#endif


};

extern Callbacks callbacks;

}

#endif // CALLBACKS_H