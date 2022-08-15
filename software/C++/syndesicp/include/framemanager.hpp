/**
 * @file framemanager.hpp
 *
 * @brief Management of frames
 *
 * @author Sébastien Deriaz
 * @date 15.08.2022
 */

#ifndef FRAME_MANAGER_H
#define FRAME_MANAGER_H

#include "callbacks.hpp"
#include "syndesi_types.hpp"

namespace syndesi {

/**
 * @brief Class to manage frames after they've been parsed by the network
 * interface
 *
 */
class FrameManager {
    class Frame {
        // A Frame instance contains a command (cmd_t) and a payload
       public:
        /**
         * @brief Construct a new Frame object from a buffer
         *
         * @param buffer
         */
        Frame(Buffer& buffer);

        /**
         * @brief Get the command ID
         *
         * @return cmd_t
         */
        cmd_t getCommand();
        /**
         * @brief Get the payload buffer
         *
         * @return Buffer
         */
        Buffer getPayload();
    };

    Callbacks callbacks;

    /*
     * Interfacing with lower layers
     */

    /**
     * @brief Method called whenever a request frame is received, called by the
     * network interface
     * 
     * @param frame
     */
    void onReceiveRequest(Frame& frame);
    /**
     * @brief Send request frame (to network interface)
     * 
     * @param frame 
     */
    void sendRequest(Frame& frame);
    /**
     * @brief Method called whenever a reply frame is received, called by the
     * network interface
     *
     * @param frame
     */
    void onReceiveReply(Frame& frame);
    /**
     * @brief Send reply frame (to network interface)
     *
     * @param frame
     */
    void sendReply(Frame& frame);
    
    
};

}  // namespace syndesi

#endif  // FRAME_MANAGER_H
