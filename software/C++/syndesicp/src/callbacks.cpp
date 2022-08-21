/* THIS FILE IS GENERATED AUTOMATICALLY
*  DO NOT EDIT
*  This file has been written by the script generate_commands.py
*  date : 22-08-20 17:15:02
*/

#include "callbacks.hpp"

namespace syndesi {

Callbacks callbacks;


void Callbacks::indication(Frame& frame) {
    Buffer* requestPayloadBuffer = frame.getPayloadBuffer();
    Payload* reply = nullptr;
    Payload* request = nullptr;

    cout << "callbacks indication with command : " << frame.getCommand() << endl;
    switch(frame.getCommand()) {
#if defined(USE_DEVICE_DISCOVER_REQUEST_CALLBACK) && defined(DEVICE_MODE)
        case commands::DEVICE_DISCOVER:
            request = new DEVICE_DISCOVER_request(requestPayloadBuffer);
            reply = new DEVICE_DISCOVER_reply();
            DEVICE_DISCOVER_request_callback(*(static_cast<DEVICE_DISCOVER_request*>(request)), static_cast<DEVICE_DISCOVER_reply*>(reply));
            break;
#endif
#if defined(USE_REGISTER_READ_16_REQUEST_CALLBACK) && defined(DEVICE_MODE)
        case commands::REGISTER_READ_16:
            request = new REGISTER_READ_16_request(requestPayloadBuffer);
            reply = new REGISTER_READ_16_reply();
            REGISTER_READ_16_request_callback(*(static_cast<REGISTER_READ_16_request*>(request)), static_cast<REGISTER_READ_16_reply*>(reply));
            break;
#endif
#if defined(USE_REGISTER_WRITE_16_REQUEST_CALLBACK) && defined(DEVICE_MODE)
        case commands::REGISTER_WRITE_16:
            cout << "register write 16" << endl;
            request = new REGISTER_WRITE_16_request(requestPayloadBuffer);
            reply = new REGISTER_WRITE_16_reply();
            REGISTER_WRITE_16_request_callback(*(static_cast<REGISTER_WRITE_16_request*>(request)), static_cast<REGISTER_WRITE_16_reply*>(reply));
            break;
#endif
#if defined(USE_SPI_READ_WRITE_REQUEST_CALLBACK) && defined(DEVICE_MODE)
        case commands::SPI_READ_WRITE:
            request = new SPI_READ_WRITE_request(requestPayloadBuffer);
            reply = new SPI_READ_WRITE_reply();
            SPI_READ_WRITE_request_callback(*(static_cast<SPI_READ_WRITE_request*>(request)), static_cast<SPI_READ_WRITE_reply*>(reply));
            break;
#endif
#if defined(USE_SPI_WRITE_ONLY_REQUEST_CALLBACK) && defined(DEVICE_MODE)
        case commands::SPI_WRITE_ONLY:
            request = new SPI_WRITE_ONLY_request(requestPayloadBuffer);
            reply = new SPI_WRITE_ONLY_reply();
            SPI_WRITE_ONLY_request_callback(*(static_cast<SPI_WRITE_ONLY_request*>(request)), static_cast<SPI_WRITE_ONLY_reply*>(reply));
            break;
#endif
#if defined(USE_I2C_READ_REQUEST_CALLBACK) && defined(DEVICE_MODE)
        case commands::I2C_READ:
            request = new I2C_READ_request(requestPayloadBuffer);
            reply = new I2C_READ_reply();
            I2C_READ_request_callback(*(static_cast<I2C_READ_request*>(request)), static_cast<I2C_READ_reply*>(reply));
            break;
#endif
#if defined(USE_I2C_WRITE_REQUEST_CALLBACK) && defined(DEVICE_MODE)
        case commands::I2C_WRITE:
            request = new I2C_WRITE_request(requestPayloadBuffer);
            reply = new I2C_WRITE_reply();
            I2C_WRITE_request_callback(*(static_cast<I2C_WRITE_request*>(request)), static_cast<I2C_WRITE_reply*>(reply));
            break;
#endif

    }

    if(reply != nullptr && _frameManager != nullptr) {
        Frame replyFrame(*reply, frame.getID());
        _frameManager->response(replyFrame);
    }
}

void Callbacks::confirm(Frame& frame) {
    Buffer* replyPayloadBuffer = frame.getPayloadBuffer();
    Payload* reply = nullptr;

    cout << "Callbacks confirm with command : " << frame.getCommand() << endl;
    switch(frame.getCommand()) {
#if defined(USE_ERROR_REPLY_CALLBACK) && defined(HOST_MODE)
        case commands::ERROR:
            reply = new ERROR_reply(replyPayloadBuffer);
            ERROR_reply_callback(*(static_cast<ERROR_reply*>(reply)));
            break;
#endif
#if defined(USE_DEVICE_DISCOVER_REPLY_CALLBACK) && defined(HOST_MODE)
        case commands::DEVICE_DISCOVER:
            reply = new DEVICE_DISCOVER_reply(replyPayloadBuffer);
            DEVICE_DISCOVER_reply_callback(*(static_cast<DEVICE_DISCOVER_reply*>(reply)));
            break;
#endif
#if defined(USE_REGISTER_READ_16_REPLY_CALLBACK) && defined(HOST_MODE)
        case commands::REGISTER_READ_16:
            reply = new REGISTER_READ_16_reply(replyPayloadBuffer);
            REGISTER_READ_16_reply_callback(*(static_cast<REGISTER_READ_16_reply*>(reply)));
            break;
#endif
#if defined(USE_REGISTER_WRITE_16_REPLY_CALLBACK) && defined(HOST_MODE)
        case commands::REGISTER_WRITE_16:
            reply = new REGISTER_WRITE_16_reply(replyPayloadBuffer);
            REGISTER_WRITE_16_reply_callback(*(static_cast<REGISTER_WRITE_16_reply*>(reply)));
            break;
#endif
#if defined(USE_SPI_READ_WRITE_REPLY_CALLBACK) && defined(HOST_MODE)
        case commands::SPI_READ_WRITE:
            reply = new SPI_READ_WRITE_reply(replyPayloadBuffer);
            SPI_READ_WRITE_reply_callback(*(static_cast<SPI_READ_WRITE_reply*>(reply)));
            break;
#endif
#if defined(USE_SPI_WRITE_ONLY_REPLY_CALLBACK) && defined(HOST_MODE)
        case commands::SPI_WRITE_ONLY:
            reply = new SPI_WRITE_ONLY_reply(replyPayloadBuffer);
            SPI_WRITE_ONLY_reply_callback(*(static_cast<SPI_WRITE_ONLY_reply*>(reply)));
            break;
#endif
#if defined(USE_I2C_READ_REPLY_CALLBACK) && defined(HOST_MODE)
        case commands::I2C_READ:
            reply = new I2C_READ_reply(replyPayloadBuffer);
            I2C_READ_reply_callback(*(static_cast<I2C_READ_reply*>(reply)));
            break;
#endif
#if defined(USE_I2C_WRITE_REPLY_CALLBACK) && defined(HOST_MODE)
        case commands::I2C_WRITE:
            reply = new I2C_WRITE_reply(replyPayloadBuffer);
            I2C_WRITE_reply_callback(*(static_cast<I2C_WRITE_reply*>(reply)));
            break;
#endif

    }
}


} // namespace syndesi