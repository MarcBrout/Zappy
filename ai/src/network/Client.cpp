//
// Created by Pierre Bougon on 20/04/17.
//

#include <vector>
#include "tools/Logger.hpp"
#include "network/Client.hpp"

zappy::network::Client::Client(uint16_t port, const std::string &hostname) : TCPClient(port, hostname)
{
    _fdManager.set_tv(300);
}

zappy::network::Client::Client() : TCPClient(0, "")
{
    _fdManager.set_tv(300);
}

void zappy::network::Client::Init(uint16_t port, std::string const &host)
{
    _port = port;
    _hostname = host;
    init();
}

std::vector<std::string> zappy::network::Client::getServerMessages()
{
    std::vector<std::string> messages;

    messages.clear();
    _fdManager.manageFD(_socket);
    _fdManager.select(_socket);
    if (_fdManager.isFdSet(_socket, _fdManager.READ))
    {
        messages = ASocket::receive();
    }
    return messages;
}

zappy::network::Client::~Client()
{
}
