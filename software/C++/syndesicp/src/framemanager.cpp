/**
 * @file framemanager.cpp
 *
 * @brief Management of frames
 *
 * @author Sébastien Deriaz
 * @date 15.08.2022
 */



#include "framemanager.hpp"


namespace syndesi {

void FrameManager::onReceiveRequest(Frame& frame) {
    Buffer replyBuffer;
    replyBuffer = callbacks.processRequest(frame.getCommand(), frame.getPayload());
    Frame replyFrame(replyBuffer);
    sendReply(replyFrame);
}





} // namespace syndesi