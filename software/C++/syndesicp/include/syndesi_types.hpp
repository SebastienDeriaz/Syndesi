/**
 * @file syndesi_types.hpp
 *
 * @brief Syndesi device types library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 08.06.2022
 */

#include <stdint.h>
#include <cstdlib>
#include <new>

#ifndef SYNDESI_TYPES_H
#define SYNDESI_TYPES_H

namespace syndesi {

typedef struct RawBuffer{
    void* data = NULL;
    size_t length = 0;
};

/**
 * @brief Buffer class
 * 
 */
class Buffer {
    public:
    /**
     * @brief Construct a new empty Buffer object with size length
     * 
     * @param length 
     */
    Buffer(size_t length) {allocate(length);}
    ~Buffer() {deallocate();}

    void allocate(size_t length);

    void deallocate();

    RawBuffer start();

    size_t length();

    RawBuffer offset(size_t offset);

    private:
    RawBuffer data;
}




typedef union {
    uint64_t value;
} FrameDeviceID;

typedef uint16_t payloadLength_t;
typedef uint16_t cmd_t;
}  // namespace syndesi

#endif