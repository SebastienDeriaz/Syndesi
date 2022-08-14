#include "frame.hpp"

namespace syndesi {

Frame::Frame(Buffer& buffer) { 
    parse(buffer);
}

Frame::Frame(Payload& payload) { build(payload); }


bool Frame::allocate(const size_t length) {
    // Free the buffer if it wasn't empty
    if(frameBuffer.data != nullptr) {
        freeBuffer();
    }
    // Allocate the new buffer
    frameBuffer.data = (char*)malloc(length);
    // Test if it was allocated correctly
    if (frameBuffer.data != nullptr) {
        frameBuffer.length = length;
    } else {
        frameBuffer.length = 0;
        throw std::bad_alloc();
    }
}

void Frame::freeBuffer() {
    if (frameBuffer.data != NULL) {
        free(frameBuffer.data);
        frameBuffer.data = NULL;
    }
    frameBuffer.length = 0;
}

size_t Frame::parse(const Buffer& buffer) {
    size_t pos = 0;
    size_t frameLength = 0;

    if (buffer.length >= MINIMUM_FRAME_LENGTH) {
        // Read length
        pos += ntoh(buffer.data + pos, (char*)&payloadLength, sizeof(payloadLength));
        // Read command
        pos += ntoh(buffer.data + pos, (char*)&command, sizeof(payloadLength));
        
        frameLength = payloadLength + sizeof(command) + sizeof(payloadLength);
        if (frameLength > buffer.length) {
            frameLength = 0;
            throw std::length_error("Invalid frame length");
        }
    } else {
        throw std::length_error("Buffer cannot fit a frame");
    }
    return frameLength;
}

Buffer& Frame::getPayloadBuffer() {
    payloadBuffer.data = frameBuffer.data + sizeof(command) + sizeof(payloadLength);
    payloadBuffer.length = payloadLength;
    return payloadBuffer;
}

Buffer& Frame::build(Payload& payload) {
    size_t pos = 0;
    payloadLength = payload.payloadLength();
    command = payload.getCommand();
    size_t frameLength =
        payloadLength + sizeof(command) + sizeof(payloadLength);
    allocate(frameLength);
    payload.build(Buffer{.data = frameBuffer.data + headerLength, .length = frameBuffer.length - headerLength});
    pos += hton((char*)&payloadLength, frameBuffer.data + pos, sizeof(payloadLength));
    pos += hton((char*)&command, frameBuffer.data + pos, sizeof(command));

    return frameBuffer;
}

cmd_t Frame::getCommand() { return command; }

Buffer& Frame::getBuffer() {
    return frameBuffer;
}

}  // namespace syndesi