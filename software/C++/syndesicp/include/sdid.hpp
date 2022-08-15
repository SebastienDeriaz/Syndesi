/**
 * @file sdid.hpp
 *
 * @brief Syndesi ID library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 14.08.2022
 */

/*
* Syndesi unique ID (sdid) allows for the identification of devices and hosts
* 
* Long version : 17 bytes long (to fit an IPv6 address alongside a header)
* | header | IPv6 or other |
* | 1 byte |    16 bytes   |
*  
* Short version : 5 bytes long (to fit an IPv4 address alongside a header)
* | header |  IPv4 or other |
* | 1 byte |     4 bytes    |
*/

#ifndef SDID_H
#define SDID_H

#include <stdint.h>
#include <cstring>

namespace syndesi {
/**
 * @brief Syndesi unique identifier for hosts and devices
 * 
 */
class SyndesiID {
    public:
        /**
         * @brief Construct a new SyndesiID from IPv4 address
         * 
         * @param IPv4 
         */
        SyndesiID(char IPv4[4]);

        /**
         * @brief Construct a new SyndesiID from IPv6 address
         * 
         * @param IPv6
         */
        SyndesiID(char IPv6[16]);

        /**
         * @brief Copy constructor
         * 
         * @param sdid 
         */
        SyndesiID(SyndesiID &sdid);
    
    private:

    enum address_type_t : unsigned char{IPV4, IPV6};

    union sdid_header_t{
        struct {
            unsigned char long_version : 1; // Long version (18 bytes), short version (6 bytes)
            address_type_t address_type : 3;
            unsigned char reserved : 4;
        }fields;
        unsigned char value;
    }header;

    union payload_t{
        union short_payload_t{
            char IPv4[4];
        }short_payload;
        union long_payload_t{
            char IPv6[16];
        }long_payload;
    }payload;
};
}

#endif // SDID_h

