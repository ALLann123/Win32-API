#include <iostream>
#include <winsock2.h>    // MUST come before windows.h
#include <ws2tcpip.h>    // windows sockets 2 definition for IP communication
#include <windows.h>     // Windows API (now after winsock2.h)

#pragma comment(lib, "ws2_32.lib") // Automatically link with the windows socket library

int main()
{
    // variable declaration
    WSADATA wsaData;           // Structure to store windows sockets implementation details
    SOCKET sock;               // socket descriptor(file handle for network connection)
    struct sockaddr_in server; // Structure to store server address
    char buffer[4096];         // buffer for received data

    std::string request; // String to build http request

    // Initialize winsock(windows sockets API)
    // MAKEWORD(2,2) requests version 2.2 of winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed.\n"; // If winsock initialization failed we get error
        return 1;
    }

    // Create a socket for communication
    /*
    AF_INET=IPV4
    SOCK_STREAM= TCP Socket type(connection-oriented)
    0= default protocol(TCP for SOCK_STREAM)
    */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed.\n";
        WSACleanup(); // Cleanup winsock before exiting
        return 1;
    }

    // configure server address structure
    server.sin_family = AF_INET;   // Set to address family IPv4
    server.sin_port = htons(5000); // Sets port number to 5000 .htons converts to network byte order

    // Convert IP address string to binary form and set in server structure
    // "192.168.1.112" is the redirector server's IP address
    // FIX: Use regular char string instead of wide char (L"string")
    if (inet_pton(AF_INET, "192.168.1.112", &server.sin_addr) <= 0)
    {
        std::cerr << "Invalid IP address.\n";
        closesocket(sock); // Close Socket before exiting
        WSACleanup();      // clean winsock
        return 1;
    }

    // Establish connection to the redirector server
    // connect() initiates TCP connection to the specified server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        std::cerr << "Connection failed.\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // build HTTP Get request to fetch command from redirector
    request = "GET /getCommand HTTP/1.1\r\n"; // Request line- get command from redirector(clear net)
    request += "Host: 192.168.1.112:5000\r\n"; // Host header- target server with port
    request += "Connection: close\r\n\r\n"; // Connection header- Close after response

    // send the HTTP request through the socket
    if (send(sock, request.c_str(), request.length(), 0) < 0)
    {
        std::cerr << "Send Failed.\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Receive response from redirector server
    // loop until no more data is received(bytesReceived==0)
    int bytesReceived;
    do
    {
        // recv() receives data from the socket into buffer
        // sizeof(buffer)-1 leaves room for null terminator
        bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0'; // NULL-terminate the received data
            std::cout << buffer;          // print the received data to console
        }
    } while (bytesReceived > 0); // continue receiving data

    // cleanup resources
    closesocket(sock); // close socket
    WSACleanup();      // shutdown winsock

    return 0;
}