/**
 * @file syndes_types.hpp
 *
 * @brief Syndesi device types library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 08.06.2022
 */

#include <stdint.h>

namespace syndesi {

typedef struct {
    uint8_t protocol_version : 3;
    uint8_t reserved : 5;
} Syndesi_header;

typedef uint16_t syndesi_length;
typedef uint16_t syndesi_cmd;

typedef uint8_t syndesi_protocol_version;

}  // namespace syndesi