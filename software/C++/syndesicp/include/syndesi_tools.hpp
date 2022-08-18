/**
 * @file syndesi_tools.hpp
 *
 * @brief Tools used with the syndesi library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 14.06.2022
 */

#include <stdint.h>
#include <cstddef>
#include <string.h>

using std::byte;

#ifndef SYNDESI_TOOLS_H
#define SYNDESI_TOOLS_H

namespace syndesi {
    /**
     * @brief Convert host endianness to network
     * 
     * @param src source buffer (host)
     * @param dest destination buffer (network)
     * @param length length of buffer
     * 
     * @return length of buffer
     */
    size_t hton(const byte* src, byte* dest, size_t length);

    /**
     * @brief Convert network endianness to host
     * 
     * @param src source buffer (network)
     * @param dest destination buffer (host)
     * @param length length of buffer
     * 
     * @return length of buffer
     */
    size_t ntoh(const byte* src, byte* dest, size_t length);
}  // namespace syndesi

#endif  // SYNDESI_TOOLS_H