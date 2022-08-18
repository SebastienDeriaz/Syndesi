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
typedef union {
    uint64_t value;
} FrameDeviceID;

typedef uint16_t payloadLength_t;
typedef uint16_t cmd_t;
}  // namespace syndesi

#endif