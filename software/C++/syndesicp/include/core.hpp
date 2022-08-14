/**
 * @file core.hpp
 *
 * @brief Syndesi core
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 09.08.2022
 */

#ifndef CORE_H
#define CORE_H

#include <iostream>

#include "frame.hpp"
#include "syndesi_types.hpp"
#include "callbacks.hpp"

namespace syndesi {

class Core {
   private:

    Frame inboundFrame;


   public:
    Core() {

    };
    ~Core(){};

    /**
     * @brief Allocate a buffer for writing the received data
     *
     * @param length length of buffer
     *
     * @return char*
     */
    Buffer bufferAllocate(size_t length);

    /**
     * @brief Parse the buffer allocated by bufferAllocate containing a request
     *
     * @param host host ip address
     */
    void parseRequest(IPAddress host);

    /**
     * @brief Parse the buffer allocated by bufferAllocate containing a reply
     *
     * @param host host ip address
     */
    void parseReply(IPAddress host);

    /**
     * @brief Parse a buffer containing a reply given as parameter (in the case the buffer already
     * exists)
     *
     * @param buffer
     * @param length
     */
    void parseReply(char* buffer, size_t length, IPAddress host);

    // Input buffer
    Buffer buffer;
};

}  // namespace syndesi

#endif  // CORE_H