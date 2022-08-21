/**
 * @file ipcontroller.cpp
 *
 * @brief IP controller
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#include "ipcontroller.hpp"

#ifdef USE_IP_CONTROLLER

namespace syndesi
{

void IPController::IP_receive(char* data, size_t length, SyndesiID& masterID) {
    unique_ptr<SyndesiID> masterID_unique = unique_ptr<SyndesiID>(new SyndesiID(masterID));
    IP_receive(data, length, masterID_unique);
}

void IPController::IP_receive(char* data, size_t length, unique_ptr<SyndesiID>& masterID) {
    unique_ptr<Buffer> ptr = make_unique<Buffer>(data, length);
    _network->IP_indication_or_confirm(ptr, masterID);
}

/*
* Higher layer
*/
void IPController::request_or_response(unique_ptr<Buffer>& buffer, SyndesiID& masterID) {
    IP_send((char*)(buffer.get()->data()), buffer.get()->length(), masterID);
}

} // namespace syndesi

#endif // USE_IP_CONTROLLER
