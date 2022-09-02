/**
 * @file interfaces.hpp
 *
 * @brief Interfaces between layers.
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#ifndef INTERFACES_H
#define INTERFACES_H

#include "buffer.hpp"
#include "frame.hpp"
#include "protocols_config.hpp"

namespace syndesi {
namespace SAP {

class IFrameManager_top {
   public:
    // From top layer
    virtual void response(Frame& payload) = 0;
};

class IFrameManager_bottom {
   public:
    // From bottom layer
    virtual void indication(Frame& frame) = 0;
    virtual void confirm(Frame& frame) = 0;
};

class INetwork_top {
   public:
    // From top layer
    virtual void request(Frame& frame) = 0;
    virtual void response(Frame& frame) = 0;
};

class IDeviceController_top;
class IHostController_top;


class INetwork_bottom {
    public:
    virtual unsigned short port() = 0;
    virtual void setCustomPort(unsigned short port) = 0;

};

class INetwork_device_bottom : public INetwork_bottom {
   public:
    virtual void indication(unique_ptr<SyndesiID>& id,
                            unique_ptr<Buffer>& buffer) = 0;
    virtual void registerIPDeviceController(
        SAP::IDeviceController_top* controller) = 0;
};

class INetwork_host_bottom  : public INetwork_bottom {
   public:
    virtual void confirm(unique_ptr<SyndesiID>& id,
                         unique_ptr<Buffer>& buffer) = 0;
    virtual void registerIPHostController(SAP::IHostController_top* controller) = 0;
};

class IController_top {
   public:
    virtual void init() = 0;

    virtual size_t readBuffer(char* buffer, size_t length) = 0;

    unique_ptr<Buffer> readFrame() {
        // Read a frame
        static const size_t HBufferLength =
            Frame::networkHeader_size + Frame::frameLength_size;
        char
            HBuffer[HBufferLength];  // Buffer for NetworkHeader and FrameLength
        Frame::frameLength_t frameLength;
        // 1. Read the network header and frame length
        readBuffer(HBuffer, HBufferLength);
        ntoh(HBuffer + Frame::networkHeader_size,
             reinterpret_cast<char*>(&frameLength), Frame::frameLength_size); 

        size_t completeFrameLength = HBufferLength + frameLength;
        // 2. Allocate a buffer knowing the complete frame size
        unique_ptr<Buffer> buffer =
            unique_ptr<Buffer>(new Buffer(completeFrameLength));

        // Copy the previous buffer (HBuffer) to the newly allocated buffer
        memcpy(buffer->data(), HBuffer, HBufferLength);

        // Read all of the data to the new buffer
        readBuffer(buffer->data() + HBufferLength,
                   buffer->length() - HBufferLength);
        // Make a copy of the id
        return buffer;
    }
};

class IDeviceController_top : public IController_top {
   protected:
    INetwork_device_bottom* network;

   public:
    IDeviceController_top(INetwork_device_bottom* _network) {
        network = _network;
        network->registerIPDeviceController(this);
    }

    IDeviceController_top(const IDeviceController_top&) = delete;
    IDeviceController_top(const IDeviceController_top&&) = delete;

    virtual void response(unique_ptr<SyndesiID>& id, unique_ptr<Buffer>& buffer) = 0;

    void indication(unique_ptr<SyndesiID> id, unique_ptr<Buffer> buffer) {
        network->indication(id, buffer);
    }
};

class IHostController_top : public IController_top {
   protected:
    INetwork_host_bottom* network;

   public:
    IHostController_top(INetwork_host_bottom* _network) {
        network = _network;
        network->registerIPHostController(this);
    }

    IHostController_top(const IHostController_top&) = delete;
    IHostController_top(const IHostController_top&&) = delete;

    virtual void request(unique_ptr<SyndesiID>& id, unique_ptr<Buffer>& buffer) = 0;

    void confirm(unique_ptr<SyndesiID> id, unique_ptr<Buffer> buffer) {
        network->confirm(id, buffer);
    }
};

}  // namespace SAP
}  // namespace syndesi

#endif  // INTERFACES_H
