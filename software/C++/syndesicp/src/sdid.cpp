/**
 * @file sdid.cpp
 *
 * @brief Syndesi ID library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 14.08.2022
 */

#include "sdid.hpp"

namespace syndesi {

SyndesiID::SyndesiID() {}

SyndesiID::SyndesiID(unsigned char* buffer, address_type_t type) {
    header.fields.address_type = type;
    header.fields.follow = false;
    header.fields.reserved = 0;
    switch(type) {
        case IPV4:
        case IPV6:
            memcpy((void*)&payload, buffer, addressSizes.at(type));
            break;
    }
}


void SyndesiID::append(unsigned char* buffer, address_type_t type) {
    if(next) {
        // Add to the next one
        next->append(buffer, type);
    }
    else {
        // Add here
        next = make_unique<SyndesiID>(buffer, type);
    }
}

SyndesiID::SyndesiID(SyndesiID& sdid) {
    memcpy(&payload, &sdid.payload, sizeof(sdid.payload));
    header.value = sdid.header.value;
}

SyndesiID::SyndesiID(Buffer* buffer) {
    // Read the header
    ntoh(buffer->data(), reinterpret_cast<byte*>(&header), sizeof(header));
    // Read the payload
    size_t address_size = addressSizes.at(header.fields.address_type);
    memcpy(reinterpret_cast<void*>(&payload), buffer->data() + sizeof(header),
           address_size);
    is_next = true;
    if (header.fields.follow) {
        Buffer subbuffer = Buffer(buffer, address_size + sizeof(header));
        next = make_unique<SyndesiID>(&subbuffer);
    }
}

unsigned int SyndesiID::reroutes() {
    size_t count = 0;
    if (next) {
        count += next->reroutes();
    }
    return count;
}

size_t SyndesiID::getTotalAdressingSize() {
    size_t size = 0;
    if (is_next) addressSizes.at(header.fields.address_type);
    if (next) size += next->getTotalAdressingSize();
    return size;
}

SyndesiID::address_type_t SyndesiID::getAddressType() {
    return header.fields.address_type;
}

void SyndesiID::buildAddressingBuffer(Buffer* buffer) {
    // Do not write itself
    size_t addressLength = 0;
    size_t offset = 0;
    if (is_next) {
        // Write itself
        hton(reinterpret_cast<byte*>(&header), buffer->data(), sizeof(header));
        addressLength = addressSizes.at(header.fields.address_type);
        memcpy(buffer->data() + sizeof(header), &payload, addressLength);
        if (next) {
            // As long as they are "next"s, write them
            Buffer subbuffer(buffer, addressLength + sizeof(header));
            next->buildAddressingBuffer(&subbuffer);
        }
    } else if (next) {
        // Do not write the master, but start with the first "next"
        next->buildAddressingBuffer(buffer);
    }
}

void SyndesiID::parseAddressingBuffer(Buffer* buffer) {
    // Read
    next = make_unique<SyndesiID>(buffer);
}
}  // namespace syndesi
