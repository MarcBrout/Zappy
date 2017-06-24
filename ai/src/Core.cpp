//
// Created by Pierre Bougon on 21/06/17.
//

#include <network/Client.hpp>
#include <vector>
#include <tools/Logger.hpp>
#include "Core.hpp"

zappy::Core::Core() : _running(false), _waitingForResponse(false)
{}

zappy::Core::~Core()
{}

void zappy::Core::run()
{
    std::vector<std::string>    servMessages;
    std::string                 command;

    _running = true;
    while (_running)
    {
        _ai.nextAction();
        //check server send
        usleep(100000);
        servMessages = network::Client::getInstance().getServerMessages();
        for (std::vector<std::string>::iterator it = servMessages.begin(); it < servMessages.end(); ++it)
            manageResponse(*it);
        servMessages.clear();
        _ai.sendAction();
        _waitingForResponse = true;
        while (_waitingForResponse)
        {
            servMessages = network::Client::getInstance().getServerMessages();
            for (std::vector<std::string>::iterator it = servMessages.begin(); it < servMessages.end(); ++it)
                manageResponse(*it);
            ::usleep(100);
        }
        ::usleep(100);
    }
}

void zappy::Core::manageResponse(std::string servMessage)
{
    Logger::log(Logger::_DEBUG_, "command received : " + servMessage);
    if (servMessage == "dead")
        _running = false;
    else if (servMessage.substr(0, servMessage.find(" ") - 1) == "message")
        _ai.setMessage(servMessage);
    else if (servMessage == "WELCOME")
    {
        // TODO change to team name
        network::Client::getInstance().send("1");
    }
    else
    {
        _waitingForResponse = false;
        _ai.setResponse(servMessage);
    }
}

