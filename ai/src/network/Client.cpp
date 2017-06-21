//
// Created by Pierre Bougon on 20/04/17.
//

#include "tools/Logger.hpp"
#include "network/Client.hpp"

zappy::network::Client::Client(uint16_t port, const std::string &hostname) : TCPClient(port, hostname)
{}

zappy::network::Client::Client() : TCPClient(0, "")
{
}

void zappy::network::Client::Init(uint16_t port, std::string const &host)
{
    _port = port;
    _hostname = host;
    init();
}


zappy::network::Client::~Client()
{
}
