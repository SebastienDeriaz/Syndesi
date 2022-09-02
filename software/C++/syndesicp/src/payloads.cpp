/* THIS FILE IS GENERATED AUTOMATICALLY
 *  DO NOT EDIT
 *  This file has been written by the script generate_commands.py
 *  date : 22-09-02 21:18:05
 */


#include "payloads.hpp"

namespace syndesi {

std::map<cmd_t, string> command_names_list = {
{0x0000, "NO_COMMAND"},
{0x0001, "ERROR"},
{0x0002, "DEVICE_DISCOVER"},
{0x0100, "REGISTER_READ_16"},
{0x0101, "REGISTER_WRITE_16"},
{0x0110, "SPI_READ_WRITE"},
{0x0111, "SPI_WRITE_ONLY"},
{0x0120, "I2C_READ"},
{0x0121, "I2C_WRITE"}
};


} //namespace syndesi