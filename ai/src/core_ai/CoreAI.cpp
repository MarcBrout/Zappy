//
// Created by Pierre Bougon on 23/06/17.
//

#include <string>
#include <network/SendCommand.hpp>
#include "core_ai/CoreAI.hpp"

void zappy::CoreAI::nextAction()
{

}

void zappy::CoreAI::sendAction()
{
    network::SendCommand::forward();
}

void zappy::CoreAI::setMessage(std::string const &message)
{
    _message.push_back(message);
}

void zappy::CoreAI::setResponse(std::string const &response)
{
    _response = response;
}
