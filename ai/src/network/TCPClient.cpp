//
// Created by Pierre Bougon on 20/04/17.
//

#include <exceptions/SocketError.hpp>
#include <cstring>
#include <tools/Logger.hpp>
#include <iostream>
#include <bits/sigthread.h>
#include <bits/signum.h>
#include <signal.h>
#include <csignal>
#include <zconf.h>
#include "network/TCPClient.hpp"

zappy::network::TCPClient::TCPClient(uint16_t port, const std::string &hostname) : ASocket(port, hostname)
{}

std::string zappy::network::TCPClient::receive(sock_t socket)
{
    std::string     data;
    char            buf[BUFFER_SIZE];
    ssize_t         ret;

    ret = ::recv(socket, buf, BUFFER_SIZE, 0);
    if (ret == -1 && errno == EINTR)
    {
        // Stopping Client
        return nullptr;
    }
    else if (ret == -1)
    {
        return nullptr;
    }
    else if (ret == 0)
        return nullptr;
    else
        data += buf;

    inputPacket.deserialize(data);
    Logger::log(Logger::DEBUG, "Client Receiving: " + inputPacket.serialize());
    return std::move(inputData);
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
        std::memset(_servAddr, 0, sizeof(_servAddr));
    }
}

bool zappy::network::TCPClient::isConnected()
{
    return _socket != -1;
}

zappy::network::TCPClient::~TCPClient()
{
}


