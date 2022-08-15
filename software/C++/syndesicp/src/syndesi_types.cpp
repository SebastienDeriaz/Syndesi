/**
 * @file syndesi_types.cpp
 *
 * @brief Syndesi device types library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 15.08.2022
 */

#include "syndesi_types.hpp"

namespace syndesi {

void Buffer::allocate(size_t length) {
    deallocate();
    data.data = std::malloc(length);
    if (data.data == nullptr) {
        throw std::bad_alloc();
    } else {
        data.length = length;
    }
}

void Buffer::deallocate() {
    if (data.data != nullptr) {
        std::free(data.data);
        data.data = nullptr;
        data.length = 0;
    }
}

RawBuffer Buffer::start() { return data; }

size_t Buffer::length() { return data.length; }

RawBuffer offset(size_t off) {
    if (off > length()) {
        // throw error
    } else {
        return RawBuffer{.data = data.data + off, .length = length() - off};
    }
}
}  // namespace syndesi