#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>

#include <syndesicp.hpp>

using namespace std;

syndesi::Core core;

void callback();

int new_socket;

int main(int argc, char const* argv[]) {
    int valread, client_fd;
    struct sockaddr_in address;
    int server_fd;
    int opt = 1;
    
    int addrlen = sizeof(address);

    char buffer[1024] = {0};

    cout << "Syndesi comtest example : device" << endl;
    cout << "Sébastien Deriaz    20.08.2022" << endl;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(core.port());

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        cout << "Waiting for command..." << endl;

        if ((new_socket = accept(server_fd, (struct sockaddr*)&address,
                                 (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        valread = read(new_socket, buffer, 1024);

        cout << "received data" << endl;
        for (int i = 0; i < valread; i++) {
            printf("%02X ", (uint8_t)buffer[i]);
        }

        syndesi::SyndesiID id = syndesi::SyndesiID();
        id.fromIPv4(address.sin_addr.s_addr, address.sin_port);


        // Received message
        core.ipController.IP_receive(buffer, valread, id);


        // Do not close the socket, leave some time for the response
        //close(new_socket);
    }

    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}

void syndesi::IPController::IP_send(char* buffer, size_t length,
                                    SyndesiID& id) {

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

    cout << "Sending data with length : " << length << endl;
    int bytes_sent = send(new_socket, buffer, length, 0);
    
    close(client_fd);
}

void syndesi::Callbacks::DEVICE_DISCOVER_request_callback(
    syndesi::DEVICE_DISCOVER_request& request,
    syndesi::DEVICE_DISCOVER_reply* reply) {}

void syndesi::Callbacks::REGISTER_READ_16_request_callback(
    syndesi::REGISTER_READ_16_request& request,
    syndesi::REGISTER_READ_16_reply* reply) {
    cout << "REGISTER READ 16 reply callback" << endl;
    // cout << "Address : " << request.
    // cout << "reply value : " << reply.data << endl;
}

void syndesi::Callbacks::REGISTER_WRITE_16_request_callback(
    syndesi::REGISTER_WRITE_16_request& request,
    syndesi::REGISTER_WRITE_16_reply* reply) {
        reply->status = REGISTER_WRITE_16_reply::OK;
    }
void syndesi::Callbacks::SPI_READ_WRITE_request_callback(
    syndesi::SPI_READ_WRITE_request& request,
    syndesi::SPI_READ_WRITE_reply* reply) {}
void syndesi::Callbacks::SPI_WRITE_ONLY_request_callback(
    syndesi::SPI_WRITE_ONLY_request& request,
    syndesi::SPI_WRITE_ONLY_reply* reply) {}
void syndesi::Callbacks::I2C_READ_request_callback(
    syndesi::I2C_READ_request& request, syndesi::I2C_READ_reply* reply) {}
void syndesi::Callbacks::I2C_WRITE_request_callback(
    syndesi::I2C_WRITE_request& request, syndesi::I2C_WRITE_reply* reply) {}
