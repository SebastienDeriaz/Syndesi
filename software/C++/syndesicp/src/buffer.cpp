/**
 * @file buffer.cpp
 *
 * @brief General purpose buffer
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#include "buffer.hpp"

namespace syndesi {

Buffer::Buffer() { _total_offset = 0; }

Buffer::Buffer(size_t length) {
    allocate(length);
    _total_offset = 0;
}

Buffer::~Buffer() { deallocate(); }

Buffer::Buffer(Buffer* parent, size_t offset, size_t length) {
    fromParent(parent, offset);
}

Buffer::Buffer(char* buffer, size_t length) {
    _data = make_shared<rawBuffer>(buffer, length);
}

Buffer::Buffer(string& data) {
    _data = make_shared<rawBuffer>(data.length());
    memcpy(_data->start(), data.c_str(), data.length());
}

void Buffer::fromParent(const Buffer* parent, size_t offset, size_t length) {
    if (offset > parent->length()) {
        throw std::out_of_range(
            "Cannot create a sub-buffer with offset greater than the parent's "
            "length");
    }
    _total_offset = parent->_total_offset + offset;
    _data = parent->_data;
    _offset = offset;
    _clipLength = length;
}

void Buffer::allocate(size_t length) {
    if (_data) {
        deallocate();
    }
    _data = make_shared<rawBuffer>(length);
}

void Buffer::deallocate() { _data = nullptr; }

void Buffer::fromBuffer(char* buffer, size_t length) {
    deallocate();
    _data = make_shared<rawBuffer>(buffer, length);
}

Buffer Buffer::offset(size_t offset, size_t length) {
    Buffer buf;
    buf.fromParent(this, offset, length);
    return buf;
}

size_t Buffer::length() const {
    // Set the max length
    size_t len = _data.get()->length() - _offset;
    // If a clip is defined and it is valid, use it
    if (_clipLength > 0 && _clipLength < len) {
        len = _clipLength;
    }
    return len;
}

size_t Buffer::getOffset() { return _offset; }

string Buffer::toString() {
    if(_data != nullptr) {
        return string(data(), length());
    }
    else {
        return "";
    }
}

string Buffer::toHex() {
    stringstream output;
    char* start = data();
    for(size_t i = 0;i<length();i++) {
        output << hex << start[i] << " ";
    }
    return output.str();
}

}  // namespace syndes