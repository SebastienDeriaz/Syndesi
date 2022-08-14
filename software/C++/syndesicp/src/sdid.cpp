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

    SyndesiID::SyndesiID(char IPv4[4]) {
        header.fields.long_version = false;
        header.fields.address_type = IPV4;
        reserved.value = 0;
        memcpy(payload.short_payload.IPv4, IPv4, sizeof(IPv4));
    }

    SyndesiID::SyndesiID(char IPv4[4]) {
        header.fields.long_version = true;
        header.fields.address_type = IPV6;
        reserved.value = 0;
        memcpy(payload.short_payload.IPv6, IPv6, sizeof(IPv6));
    }

    SyndesiID::SyndesiID(SyndesiID &sdid) {
        memcpy(&payload, &sdid.payload, sizeof(sdid.payload));
        header = sdid.header;
        reserved = sdid.reserved;
    }
}

