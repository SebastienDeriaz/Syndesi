/**
 * @file syndesi.cpp
 *
 * @brief Syndesi device library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 09.06.2022
 */

#include "../include/syndesi.hpp"



namespace syndesi {








void parsePacket(char* buffer, size_t length) {
    
    Syndesi_header header = buffer[0];
    syndesi_cmd command = 

}

}