#include "frame.hpp"

namespace syndesi {

Frame::Frame(Payload& payload, unique_ptr<SyndesiID>& id) {
    _id = move(id);
    // Set the values
    payloadLength = payload.payloadLength();
    command = payload.getCommand();

    // TODO update
    networkHeader.value = 0;
    networkHeader.fields.follow = false;
    networkHeader.fields.request_nReply = true;
    networkHeader.fields.routing = _id->reroutes() > 0 ? true : false;

    // Calculate the length of the frame
    size_t addressing_size = _id->getTotalAdressingSize();
    size_t packetLength = 1 + addressing_size + sizeof(cmd_t) +
                          sizeof(payloadLength) + payloadLength;
    size_t pos = 0;
    

    // Create a buffer
    _buffer.reset(new Buffer(packetLength));
    // Write networkHeader
    pos += hton(reinterpret_cast<byte*>(&networkHeader), _buffer->data(),
                networkHeader_size);
    // Write ID(s) (start at addressingHeader_size)
    Buffer IDBuffer(_buffer.get(), pos, addressing_size);
    _id.get()->buildAddressingBuffer(&IDBuffer);
    pos += addressing_size;

    // Write cmd_t
    pos += hton(reinterpret_cast<byte*>(&command), _buffer.get()->data() + pos,
                command_size);

    // Write payload length
    pos += hton(reinterpret_cast<byte*>(&payloadLength),
                _buffer.get()->data() + pos, payloadLength_size);
    // Write payload
    Buffer payloadBuffer(_buffer.get(), pos);
    payload.build(&payloadBuffer);

    for(size_t i = 0;i<_buffer->length();i++) {
        printf("%02X", (char)_buffer->data()[i]);
    }
}

Frame::Frame(unique_ptr<Buffer>& buffer, unique_ptr<SyndesiID>& id) {
    _id = move(id);
    _buffer = std::move(buffer);
    size_t pos = 0;
    // Read network header
    pos += ntoh(_buffer.get()->data() + pos,
                reinterpret_cast<byte*>(&networkHeader), networkHeader_size);
    // Check if the frame contains a SyndesiID (to identify a sub-device)
    if (networkHeader.fields.routing) {
        // Create a buffer for SyndesiID to read
        Buffer buffer = Buffer(_buffer.get(), pos);
        _id->parseAddressingBuffer(&buffer);
        pos += _id->getTotalAdressingSize();
    }
    // Read command
    pos += ntoh(_buffer->data() + pos, reinterpret_cast<byte*>(&command),
                command_size);
    // Read payload length
    pos += ntoh(_buffer->data() + pos, reinterpret_cast<byte*>(&payloadLength),
                payloadLength_size);

    _payloadBuffer = make_unique<Buffer>(_buffer.get(), pos);
}

cmd_t Frame::getCommand() { return command; }

Buffer* Frame::getPayloadBuffer() { return _payloadBuffer.get(); }

}  // namespace syndesi