/**
 * @file syndesi.cpp
 *
 * @brief Syndesi device library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 09.06.2022
 */

#include "core.hpp"

namespace syndesi {

Buffer Core::bufferAllocate(size_t length) {
    inboundFrame.allocate(length);
    return inboundFrame.getBuffer();
}

void Core::parseBuffer(IPAddress host) {
    // We assume there's only one frame per buffer
    inboundFrame.parse(host);
    callbacks.processRequest(inboundFrame.getCommand(), inboundFrame.getPayloadBuffer());
    inboundFrame.deallocate();

    size_t start = 0;
    size_t frameLength = 0;
    for (start = 0; start < inboundFrame.getBuffer().length; start += frameLength) {
        frameLength += inboundFramey.parse(Buffer{.data = &buffer[start], .length = length});
        if (frameLength == 0) {
            throw std::length_error("No frame in buffer or frame is invalid");
            break;
        }
        else {
            cout << "process request : " << inboundFrame.getCommand() << endl;
            
        }
    }
}

void Core::parseReply(IPAddress host) {
    // Call the parseReply function with the local buffer
    parseReply(buffer.data, buffer.length, host);
}

void Core::parseReply(char* buffer, size_t length, IPAddress host) {
    // Find frames inside the buffer
    size_t start = 0;
    size_t frameLength = 0;
    Frame frame;
    for (start = 0; start < length; start += frameLength) {
        frameLength += frame.parse(Buffer{.data = &buffer[start], .length = length});
        if (frameLength == 0) {
            throw std::length_error("No frame in buffer or frame is invalid");
            break;
        }
        else {
            cout << "processReply" << endl;
            callbacks.processReply(frame.getCommand(), frame.getPayloadBuffer());
        }
    }
    bufferFree();
}

void Core::bufferFree() {
    free(buffer.data);
    buffer.data = NULL;
    buffer.length = 0;
}
}  // namespace syndesi