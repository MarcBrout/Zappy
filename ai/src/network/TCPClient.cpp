//
// Created by Pierre Bougon on 20/04/17.
//

#include <exceptions/SocketError.hpp>
#include <cstring>
#include <tools/Logger.hpp>
#include <unistd.h>
#include <csignal>
#include "network/TCPClient.hpp"

zappy::network::TCPClient::TCPClient(uint16_t port, const std::string &hostname)
        : ASocket(port, hostname), buf(""), head(0), tail(0)
{}

std::vector<std::string> zappy::network::TCPClient::receive(sock_t socket)
{
    std::vector<std::string>        commands;
    ssize_t                         ret;
    char                            buffer[BUFFER_SIZE];

    commands.clear();
    while (head != tail)
    {
        ret = ::recv(socket, buffer, BUFFER_SIZE, 0);
        if (ret == -1 && errno == EINTR)
        {
            // Stopping Client
            disconnect();
            return commands;
        }
        else if (ret == -1)
        {
            disconnect();
            return commands;
        }
        else if (ret == 0)
        {
            //todo
            return commands;
        }
        else
        {
            manageBuffer(buffer);
            commands = splitReceived();
        }
    }
    return std::move(commands);
}

void zappy::network::TCPClient::send(const std::string &data, zappy::network::sock_t socket)
{
    std::string tosend;

    tosend = data + END_OF_COMMAND;
    Logger::log(Logger::DEBUG, "Client Sending: " + data);
    if (::send(socket, tosend.c_str(), tosend.size(), 0) == -1)
        throw network::SocketError("Cannot send to the socket");
}

void zappy::network::TCPClient::connect()
{
	Logger::log(Logger::DEBUG, "Connect");
    _server = ::gethostbyname(_hostname.c_str());
    if (!_server)
        throw network::SocketError("No such host");
    //TODO
    ::bcopy((char *)_server->h_addr_list[0], (char *)&_servAddr.sin_addr.s_addr, static_cast<size_t >(_server->h_length));
    if (::connect(_socket, (sockaddr *)(&_servAddr), sizeof(_servAddr)) == -1)
        throw network::SocketError("Cannot connect to server");
}

void zappy::network::TCPClient::disconnect()
{
    if (_socket >= 0)
    {
        close(_socket);
        _socket = -1;
        _server = nullptr;
        std::memset(&_servAddr, 0, sizeof(_servAddr));
    }
}

bool zappy::network::TCPClient::isConnected()
{
    return _socket != -1;
}

zappy::network::TCPClient::~TCPClient()
{
}

void zappy::network::TCPClient::manageBuffer(char const *buffer)
{
    for (size_t i = 0; i < BUFFER_SIZE; ++i)
    {
        buf[tail % BUFFER_SIZE] = buffer[i];
        ++tail;
    }
}

std::vector<std::string> zappy::network::TCPClient::splitReceived()
{
    std::string command;
    std::vector<std::string> listCommands;
    size_t tmpHead = head;

    for (size_t i = 0; i < BUFFER_SIZE; ++i)
    {
        if (tmpHead == tail)
            break;
        if (buf[tmpHead % BUFFER_SIZE] == END_OF_COMMAND)
        {
            listCommands.push_back(command);
            command.clear();
            head = (tmpHead + 1) % BUFFER_SIZE;
        }
        else
            command += buf[head % BUFFER_SIZE];
        ++tmpHead;
    }
    return std::move(listCommands);
}


