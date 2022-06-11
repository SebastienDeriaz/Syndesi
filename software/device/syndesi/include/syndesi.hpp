/**
 * @file syndesi.hpp
 *
 * @brief Syndesi device library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 07.06.2022
 */

#include <vector>

#include "commands.hpp"
#include "syndesi_types.hpp"

using namespace std;

namespace syndesi {
class Syndesi_frame {
    Syndesi_frame();
    ~Syndesi_frame();

   private:
    Syndesi_header header;
    syndesi_cmd command;
    vector<byte> data;

   public:
    syndesi_protocol_version protocolVersion();
};

static class SyndesiCore {
    vector<Syndesi_frame> framesBuffer;

    // Callback function containing a switch for each command
    void (*processCommand)(syndesi_cmd command, const vector<byte> &data);

    void parsePacket(const vector<byte> data);
};
}  // namespace syndesi