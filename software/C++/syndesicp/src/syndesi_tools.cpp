/**
 * @file syndesi_tools.cpp
 *
 * @brief Tools used by the Syndesi library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 14.06.2022
 */


#include "syndesi_tools.hpp"

namespace syndesi {



size_t hton(const byte* src, byte* dest, size_t length) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    // System's endianness is the same as the network
    memcpy(dest, src, length);
#else
    // System's endianness is different from the network
    for (size_t i=0; i < length; i++) {
        dest[length-1-i] = src[i];
    }
#endif
    return length;
}

size_t ntoh(const byte* src, byte* dest, size_t length) {
    // The function is exactly the same as hton, they both exist for clarity reasons
    hton(src, dest, length);
    return length;
}

/*
size_t readBytes(const char* src, char* dest, size_t dest_length, Endian dest_endian) {
    bool endianness_difference = systemEndianness != dest_endian;
    src += endianness_difference ? dest_length - 1 : 0;
    for (int i = 0; i < dest_length; i++) {
        *dest = *src;
        dest++;
        endianness_difference ? src-- : src++;
    }
    return dest_length;
}

size_t writeBytes(char* src, char* dest, size_t dest_length, Endian src_endian) {
    // The read function is exactly the same
    return readBytes(src, dest, dest_length, src_endian);
}

size_t readBuffer(const char* buffer, size_t position, char* dest, size_t dest_length, Endian dest_endian) {
    return position + readBytes(buffer + position, dest, dest_length, dest_endian);
}

size_t writeBuffer(char* buffer, size_t position, char* dest, size_t src_length, Endian src_endian) {
    return position + writeBytes(buffer + position, dest, src_length, src_endian);
}*/
}