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

#include <cstddef>
#include <cstring>
#include <map>
#include <memory>

#include "buffer.hpp"
#include "syndesi_tools.hpp"

using namespace std;

namespace syndesi {
/**
 * @brief Syndesi unique identifier for hosts and devices
 *
 */
class SyndesiID {
   public:
    enum address_type_t : unsigned char { IPV4 = 0, IPV6 = 1 };

   private:
    static const int IPv4_size = 4;
    static const int IPv6_size = 16;

    union sdid_header_t {
        struct {
            address_type_t address_type : 4;
            bool follow : 1;
            unsigned char reserved : 3;
        } fields;
        byte value;
    };

    const std::map<address_type_t, size_t> addressSizes = {{IPV4, IPv4_size},
                                                           {IPV6, IPv6_size}};

   public:
        /**
     * @brief Default constructor
     *
     */
    SyndesiID();

    /**
     * @brief Construct a new SyndesiID object from the given buffer and address type
     * 
     * @param buffer 
     * @param type 
     */
    SyndesiID(unsigned char* buffer, address_type_t type);

    /**
     * @brief Create a sub-SyndesiID object (adds at the end of the list)
     * 
     * @param buffer
     * @param type
     */
    void append(unsigned char* buffer, address_type_t type);

    /**
     * @brief Construct a new SyndesiID object from an addressingHeader. The
     * resulting object is a child of a base SyndesiID object
     *
     * @param buffer
     * 
     * @note needs to be public for the recursion to work
     */
    SyndesiID(Buffer* buffer);

   public:
    /**
     * @brief Copy constructor
     *
     * @param sdid
     */
    SyndesiID(SyndesiID& sdid);

    SyndesiID& operator=(const SyndesiID&) = default;

    /**
     * @brief Count the number re-routes (recursive)
     *
     */
    unsigned int reroutes();

    /**
     * @brief Gets the total adressing size, all addresses combined (recursive)
     *
     */
    size_t getTotalAdressingSize();

    /**
     * @brief Get the Address type
     *
     * @return address_type_t
     */
    address_type_t getAddressType();

    /**
     * @brief Write Syndesi ID(s) to the given buffer
     *
     * @param buffer
     */
    void buildAddressingBuffer(Buffer* buffer);

    /**
     * @brief Read Syndesi ID(s) from the given buffer
     *
     * @param buffer
     */
    void parseAddressingBuffer(Buffer* buffer);

   private:
    // Next SyndesiID in case there's one (re-routing)
    unique_ptr<SyndesiID> next = nullptr;
    sdid_header_t header;

    // If this object is a next of a previous SyndesiID
    // false only for the master
    bool is_next = false;

    union payload_t {
        unsigned char IPv4[IPv4_size];
        unsigned char IPv6[IPv6_size];
    } payload;
};
}  // namespace syndesi

#endif  // SDID_h
