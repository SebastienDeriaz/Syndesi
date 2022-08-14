/**
 * @file frame.hpp
 *
 * @brief Frame library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 27.06.2022
 */

/*
    |       Frame Header       |                       |
    |----------------|---------|-----------------------|
    | payload length | command |         payload       |
    |   2 bytes      | 2 bytes |  payload_length bytes |
*/


#ifndef FRAME_H
#define FRAME_H

#include <cstdlib>
#include <iostream>

using namespace std;

#include "syndesi_types.hpp"
#include "payloads.hpp"

namespace syndesi {

class Frame {
   private:
    cmd_t command;
    payloadLength_t payloadLength;
    Buffer frameBuffer{.data = NULL, .length = 0};
    Buffer payloadBuffer{.data = NULL, .length = 0};

    void freeBuffer();

    static const size_t MINIMUM_FRAME_LENGTH = 4;

    static const size_t headerLength = sizeof(cmd_t) + sizeof(payloadLength_t);

   public:
    /**
     * @brief Construct a new empty frame object
     *
     */
    Frame(){};

    /**
     * @brief Destroy the Frame object
     * 
     */
    ~Frame(){freeBuffer();}

    /**
     * @brief Construct a new Frame object from a buffer
     *
     * @details The payload data is written by the payload class by initialized by this function
     *
     * @param command
     * @param payloadLength_t
     */
    Frame(Buffer& buffer);

    /**
     * @brief Construct a new Frame object from a payload
     * 
     * @param payload
     */
    Frame(Payload& payload);


    /**
     * @brief Allocate a buffer of length 'length'
     * 
     * @param length 
     * @return true if the buffer was allocated correctly
     * @return false otherwise
     */
    bool allocate(const size_t length);





    /**
     * @brief Retrieve command and payloadLength from a buffer containing a frame
     * 
     * @param buffer 
     * @return size_t the size of the found frame. 0 if no frame was found
     */
    size_t parse(const Buffer& buffer);

    /**
     * @brief Build a frame from a payload
     * 
     * @param payload 
     * 
     * @return The frame buffer
     */
    Buffer& build(Payload& payload);

    /**
     * @brief Get the frame buffer (for outgoing frame)
     * 
     * @return Buffer&
     */
    Buffer& getBuffer();

    /**
     * @brief Get the Payload Buffer (for ingoing frame)
     * 
     * @return Buffer& 
     */
    Buffer& getPayloadBuffer();

    /**
     * @brief Get the command ID
     * 
     * @return cmd_t
     */
    cmd_t getCommand();    
};

}  // namespace syndesi

#endif  // FRAME_H