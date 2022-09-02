#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <limits>
#include <syndesicp.hpp>

using namespace std;
using namespace syndesi;

Core core;

class IPController : SAP::IHostController_top {
    int sock = 0;

    enum State { IDLE, CONNECTED };
    State state;

   public:
    IPController(SAP::INetwork_host_bottom* _network)
        : IHostController_top(_network){};
    void init() {
        
        cout << "init, socket = " << sock << endl;
    }

    void request(unique_ptr<SyndesiID>& id, unique_ptr<Buffer>& buffer) {

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return;
        }

        cout << "request, sock = " << sock << endl;
        struct sockaddr_in serv_addr;

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(id->getIPPort());

        if (state == IDLE) {
            if (inet_pton(AF_INET, id->str().data(), &serv_addr.sin_addr) <=
                0) {
                printf("\nInvalid address/ Address not supported \n");
                return;
            }

            if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) <
                0) {
                printf("\nConnection Failed\n");
                return;
            }
            state = CONNECTED;

            int bytes_sent = send(sock, buffer->data(), buffer->length(), 0);
            unique_ptr<Buffer> frameBuffer = readFrame();
            network->confirm(id, frameBuffer);

            cout << "closing socket" << endl;
            close(sock);
            state = IDLE;
        }
    }

    size_t readBuffer(char* buffer, size_t length) {
        int valread = read(sock, buffer, length);

        for (int i = 0; i < valread; i++) {
            printf("%02X ", (uint8_t)buffer[i]);
        }
        return valread;
    }

    void setCustomPort(unsigned short port) { network->setCustomPort(port); }
};

/*void callback(syndesi::REGISTER_READ_16_request& request,
              syndesi::REGISTER_READ_16_reply& reply);*/

/**
 * @brief Send command with the desired ID
 *
 * @param commandID
 * @return true if the ID is valid
 * @return false if the ID is invalid
 */
bool sendCommand(cmd_t commandID);

IPController controller(&core.network);
syndesi::SyndesiID deviceID;

int main() {
    struct sockaddr_in address;
    char buffer[1024] = {0};
    int choice;
    string ip;

    controller.init();

    bool validIPAddress = true;

    cout << "Syndesi comtest example : host" << endl;
    cout << "Sébastien Deriaz    20.08.2022" << endl << endl;

    do {
        choice = 0;
        cout << endl << endl;
        cout << "=== Options ===" << endl;
        cout << " 1) Set device IP address" << endl;
        cout << " 2) Set custom port" << endl;
        cout << " 3) List commands" << endl;
        cout << " 4) Send command" << endl;
        cout << " 0) exit" << endl;
        cout << " choice : " << flush;
        // cin >> choice;
        scanf("%d", &choice);
        // cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer
        // before taking new

        ip = "127.0.0.1";
        deviceID.parseIPv4(ip);

        switch (choice) {
            case 1:

                do {
                    cout << "Please enter an IPv4 address : ";
                    cin >> ip;
                    validIPAddress = deviceID.parseIPv4(ip);
                    if (!validIPAddress) {
                        cout << "Invalid IP address" << endl;
                    }
                } while (!validIPAddress);
                break;
            case 2:
                unsigned short customPort;
                cout << "Enter custom port : ";
                cin >> customPort;
                controller.setCustomPort(customPort);
                break;
            case 3:
                // List commands
                for(auto const& [cmd, name] : core.commands_names()) {
                    printf("  0x%04X : %s\n", cmd, name.c_str());
                }

                break;
            case 4:
                syndesi::cmd_t commandID;
                if (validIPAddress) {
                    cout << "Please enter a command ID (hex) : 0x";
                    commandID = 0x0101;
                    cin >> hex >> commandID;
                    while (!sendCommand(commandID))
                        ;
                } else {
                    cout << "Enter a valid address" << endl;
                }
                break;
        }
        cin.clear();

    } while (choice != 0);
    return 0;
}

bool sendCommand(cmd_t commandID) {
    Payload* payload = nullptr;
    switch (commandID) {
        case DEVICE_DISCOVER:
            break;
        case REGISTER_READ_16:
            payload = new REGISTER_READ_16_request();
            cout << "Enter a read address : ";
            cin >> ((REGISTER_READ_16_request*)payload)->address;
            break;
        case REGISTER_WRITE_16:
            payload = new REGISTER_WRITE_16_request();
            cout << "Enter a write address : ";
            cin >> dec >> ((REGISTER_WRITE_16_request*)payload)->address;
            cout << "Enter data to write (uint16_t) :";
            cin >> dec >> ((REGISTER_WRITE_16_request*)payload)->data;
            break;
        case SPI_READ_WRITE:
        case SPI_WRITE_ONLY:
        case I2C_READ:
        case I2C_WRITE:
        default:
            break;
    }
    cout << endl;
    if (payload != nullptr) {
        core.sendRequest(*payload, deviceID);
    }
    return payload != nullptr ? true : false;
}

void syndesi::Callbacks::ERROR_reply_callback(syndesi::ERROR_reply& reply) {
    cout << "ERROR_reply_callback" << endl;
    cout << "    error code = " << reply.error_code << endl;
}
void syndesi::Callbacks::REGISTER_READ_16_reply_callback(
    syndesi::REGISTER_READ_16_reply& reply) {
    cout << "REGISTER_READ_16_reply_callback" << endl;
    cout << "    data = " << hex << reply.data << endl;
}
void syndesi::Callbacks::DEVICE_DISCOVER_reply_callback(
    syndesi::DEVICE_DISCOVER_reply& reply) {
        cout << "DEVICE_DISCOVER_reply_callback" << endl;
        cout << "    description = " << reply.description.toString() << " (" << reply.description.length() << ")" << endl;
        cout << "    device version = " << reply.device_version << endl;
        cout << "    ID = " << reply.ID.toHex() << endl;
        cout << "    name = " << reply.name.toString() << endl;
        cout << "    syndesi protocol version = " << reply.syndesi_protocol_version << endl;
    }
void syndesi::Callbacks::REGISTER_WRITE_16_reply_callback(
    syndesi::REGISTER_WRITE_16_reply& reply) {
    cout << "REGISTER_WRITE_16_reply_callback" << endl;
    cout << "    status = ";
    switch (reply.status) {
        case REGISTER_WRITE_16_reply::OK:
            cout << "ok";
            break;
        case REGISTER_WRITE_16_reply::NOK:
            cout << "nok";
            break;
    }
    cout << endl;
}
void syndesi::Callbacks::SPI_READ_WRITE_reply_callback(
    syndesi::SPI_READ_WRITE_reply& reply) {
        cout << "SPI_READ_WRITE_reply_callback" << endl;
        cout << "    read data = " << reply.read_data.toHex() << " (" << reply.read_data.length() << ")" << endl;
    }
void syndesi::Callbacks::SPI_WRITE_ONLY_reply_callback(
    syndesi::SPI_WRITE_ONLY_reply& reply) {
        cout << "SPI_WRITE_ONLY_reply_callback" << endl;
        cout << "    status = " << reply.status << endl;
    }
void syndesi::Callbacks::I2C_READ_reply_callback(
    syndesi::I2C_READ_reply& reply) {
        cout << "I2C_READ_reply_callback" << endl;
        cout << "    read data = " << reply.read_data.toHex() << " (" << reply.read_data.length() << ")" << endl;
    }
void syndesi::Callbacks::I2C_WRITE_reply_callback(
    syndesi::I2C_WRITE_reply& reply) {
        cout << "I2C_WRITE_reply_callback" << endl;
        cout << "    status = " << reply.status << endl;
    }
