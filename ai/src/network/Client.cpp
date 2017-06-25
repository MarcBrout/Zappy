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
        messages = receive();
    }
    return messages;
}

void zappy::network::Client::auth(std::string teamName)
{
    bool welcome = false;
    bool accepted = false;
    bool placed = false;
    std::vector<std::string> servMessages;
    int nb, x, y;

    while (!welcome)
    {
        servMessages = network::Client::getInstance().getServerMessages();
        for (std::vector<std::string>::iterator it = servMessages.begin(); it < servMessages.end(); ++it)
        {
            if (*it == "WELCOME")
                welcome = true;
        }
    }
    send(teamName);
    while (!accepted && !placed)
    {
        servMessages = network::Client::getInstance().getServerMessages();
        for (std::vector<std::string>::iterator it = servMessages.begin(); it < servMessages.end(); ++it)
        {
            if (!accepted && *it != "")
            {
                nb = std::atoi(it->c_str());
                if (nb >= 1)
                    accepted = true;
                else
                {
                    std::cout << "Chose another team : ";
                    std::getline(std::cin, teamName);
                    send(teamName);
                }
            }
            else if (*it != "")
            {
                x = std::atoi(it->substr(0, it->find(" ")).c_str());
                y = std::atoi(it->substr(it->find(" ") + 1).c_str());
                placed = true;
            }
        }
    }
}

zappy::network::Client::~Client()
{
}
