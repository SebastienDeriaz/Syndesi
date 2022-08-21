#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <limits>

#include <iostream>
#include <syndesicp.hpp>

using namespace std;
using namespace syndesi;

syndesi::Core core;

void callback(syndesi::REGISTER_READ_16_request& request,
              syndesi::REGISTER_READ_16_reply& reply);

int valread;

/**
 * @brief Send command with the desired ID
 *
 * @param commandID
 * @return true if the ID is valid
 * @return false if the ID is invalid
 */
bool sendCommand(cmd_t commandID);
syndesi::SyndesiID id;

int main() {
    struct sockaddr_in address;
    char buffer[1024] = {0};
    int choice = 0;
    string ip;

    bool validIPAddress = true;

    cout << "Syndesi comtest example : host" << endl;
    cout << "Sébastien Deriaz    20.08.2022" << endl << endl;

    

    do {
        cout << endl << endl;
        cout << "=== Options ===" << endl;
        cout << " 1) Set device IP address" << endl;
        cout << " 2) Set custom port" << endl;
        cout << " 3) Send command" << endl;
        cout << " 0) exit" << endl;
        cout << " choice : ";
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:

                do {
                    cout << "Please enter an IPv4 address : ";
                    cin >> ip;
                    validIPAddress = id.parseIPv4(ip);
                    if (!validIPAddress) {
                        cout << "Invalid IP address" << endl;
                    }
                } while (!validIPAddress);
                break;
            case 2:
                unsigned short customPort;
                cout << "Choice 2" << endl;
                cout << "Enter custom port : ";
                cin >> customPort;
                core.setCustomPort(customPort);
                break;
            case 3:
                syndesi::cmd_t commandID;
                cout << "Choice 3" << endl;
                if (validIPAddress) {
                    cout << "Please enter a command ID (hex) : 0x";
                    commandID = 0x0101;
                    cin >> hex >> commandID;
                    cout << "main id : " << id.str() << endl;
                    while (!sendCommand(commandID));
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
            cin >> ((REGISTER_WRITE_16_request*)payload)->address;
            cout << "Enter data to write (uint16_t) :";
            cin >> ((REGISTER_WRITE_16_request*)payload)->data;
            break;
        case SPI_READ_WRITE:
        case SPI_WRITE_ONLY:
        case I2C_READ:
        case I2C_WRITE:
        default:
            break;
    }
    if (payload != nullptr) {
        core.sendRequest(*payload, id);
    }
    return payload != nullptr ? true : false;
}

void syndesi::IPController::IP_send(char* buffer, size_t length,
                                    syndesi::SyndesiID& id) {
    int client_fd;
    int sock = 0;
    struct sockaddr_in serv_addr;

    cout << "ip send" << endl;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(id.getIPPort());

    cout << "address : " << id.str() << endl;
    if (inet_pton(AF_INET, id.str().data(), &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return;
    }

    if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr,
                             sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return;
    }
    cout << "Sending data with length : " << length << endl;
    int bytes_sent = send(sock, buffer, length, 0);

    // Do not close, we need to wait for the reply

    // Wait for reply
    valread = read(sock, buffer, 1024);
    // The id may be wrong here
    core.ipController.IP_receive(buffer, length, id);

}

void syndesi::Callbacks::ERROR_reply_callback(syndesi::ERROR_reply& reply) {}
void syndesi::Callbacks::REGISTER_READ_16_reply_callback(
    syndesi::REGISTER_READ_16_reply& reply) {
    cout << "register read 16 reply callback" << endl;
}
void syndesi::Callbacks::DEVICE_DISCOVER_reply_callback(
    syndesi::DEVICE_DISCOVER_reply& reply) {}
void syndesi::Callbacks::REGISTER_WRITE_16_reply_callback(
    syndesi::REGISTER_WRITE_16_reply& reply) {
        cout << "Register write 16 reply callback" << endl;
    }
void syndesi::Callbacks::SPI_READ_WRITE_reply_callback(
    syndesi::SPI_READ_WRITE_reply& reply) {}
void syndesi::Callbacks::SPI_WRITE_ONLY_reply_callback(
    syndesi::SPI_WRITE_ONLY_reply& reply) {}
void syndesi::Callbacks::I2C_READ_reply_callback(
    syndesi::I2C_READ_reply& reply) {}
void syndesi::Callbacks::I2C_WRITE_reply_callback(
    syndesi::I2C_WRITE_reply& reply) {}
