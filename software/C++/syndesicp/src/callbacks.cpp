/* THIS FILE IS GENERATED AUTOMATICALLY
*  DO NOT EDIT
*  This file has been written by the script generate_commands.py
*  date : 22-08-15 16:39:29
*/

#include "callbacks.hpp"

namespace syndesi {

Callbacks callbacks;


Buffer Callbacks::processRequest(cmd_t command, Buffer& payloadBuffer) {
    Buffer replyBuffer;
    replyBuffer.data = nullptr;
    replyBuffer.length = 0;
    switch(command) {
#ifdef USE_DEVICE_DISCOVER_REQUEST_CALLBACK
        case commands::DEVICE_DISCOVER:
                DEVICE_DISCOVER_request request(payloadBuffer);
                DEVICE_DISCOVER_reply reply;
                DEVICE_DISCOVER_request_callback(request, reply);
            break;
#endif
#ifdef USE_REGISTER_READ_16_REQUEST_CALLBACK
        case commands::REGISTER_READ_16:
                REGISTER_READ_16_request request(payloadBuffer);
                REGISTER_READ_16_reply reply;
                REGISTER_READ_16_request_callback(request, reply);
            break;
#endif
#ifdef USE_REGISTER_WRITE_16_REQUEST_CALLBACK
        case commands::REGISTER_WRITE_16:
                REGISTER_WRITE_16_request request(payloadBuffer);
                REGISTER_WRITE_16_reply reply;
                REGISTER_WRITE_16_request_callback(request, reply);
            break;
#endif
#ifdef USE_SPI_READ_WRITE_REQUEST_CALLBACK
        case commands::SPI_READ_WRITE:
                SPI_READ_WRITE_request request(payloadBuffer);
                SPI_READ_WRITE_reply reply;
                SPI_READ_WRITE_request_callback(request, reply);
            break;
#endif
#ifdef USE_SPI_WRITE_ONLY_REQUEST_CALLBACK
        case commands::SPI_WRITE_ONLY:
                SPI_WRITE_ONLY_request request(payloadBuffer);
                SPI_WRITE_ONLY_reply reply;
                SPI_WRITE_ONLY_request_callback(request, reply);
            break;
#endif
#ifdef USE_I2C_READ_REQUEST_CALLBACK
        case commands::I2C_READ:
                I2C_READ_request request(payloadBuffer);
                I2C_READ_reply reply;
                I2C_READ_request_callback(request, reply);
            break;
#endif
#ifdef USE_I2C_WRITE_REQUEST_CALLBACK
        case commands::I2C_WRITE:
                I2C_WRITE_request request(payloadBuffer);
                I2C_WRITE_reply reply;
                I2C_WRITE_request_callback(request, reply);
            break;
#endif

    }
    return replyBuffer;
}

void Callbacks::processReply(cmd_t command, Buffer& payloadBuffer) {
    switch(command) {
#ifdef USE_ERROR_REPLY_CALLBACK
        case commands::ERROR:
                ERROR_reply reply(payloadBuffer);
                ERROR_reply_callback(reply);
            break;
#endif
#ifdef USE_DEVICE_DISCOVER_REPLY_CALLBACK
        case commands::DEVICE_DISCOVER:
                DEVICE_DISCOVER_reply reply(payloadBuffer);
                DEVICE_DISCOVER_reply_callback(reply);
            break;
#endif
#ifdef USE_REGISTER_READ_16_REPLY_CALLBACK
        case commands::REGISTER_READ_16:
                REGISTER_READ_16_reply reply(payloadBuffer);
                REGISTER_READ_16_reply_callback(reply);
            break;
#endif
#ifdef USE_REGISTER_WRITE_16_REPLY_CALLBACK
        case commands::REGISTER_WRITE_16:
                REGISTER_WRITE_16_reply reply(payloadBuffer);
                REGISTER_WRITE_16_reply_callback(reply);
            break;
#endif
#ifdef USE_SPI_READ_WRITE_REPLY_CALLBACK
        case commands::SPI_READ_WRITE:
                SPI_READ_WRITE_reply reply(payloadBuffer);
                SPI_READ_WRITE_reply_callback(reply);
            break;
#endif
#ifdef USE_SPI_WRITE_ONLY_REPLY_CALLBACK
        case commands::SPI_WRITE_ONLY:
                SPI_WRITE_ONLY_reply reply(payloadBuffer);
                SPI_WRITE_ONLY_reply_callback(reply);
            break;
#endif
#ifdef USE_I2C_READ_REPLY_CALLBACK
        case commands::I2C_READ:
                I2C_READ_reply reply(payloadBuffer);
                I2C_READ_reply_callback(reply);
            break;
#endif
#ifdef USE_I2C_WRITE_REPLY_CALLBACK
        case commands::I2C_WRITE:
                I2C_WRITE_reply reply(payloadBuffer);
                I2C_WRITE_reply_callback(reply);
            break;
#endif

    }
}


} // namespace syndesi