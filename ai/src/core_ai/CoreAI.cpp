//
// Created by Pierre Bougon on 23/06/17.
//

#include <string>
#include <network/SendCommand.hpp>
#include "core_ai/CoreAI.hpp"

void zappy::CoreAI::nextAction()
{
}

void zappy::CoreAI::sendAction(CoreAI::ACTION action, const std::string &str)
{
  _actions[action](str);
}

void zappy::CoreAI::setMessage(std::string const &message)
{
  _message.push_back(message);
}

void zappy::CoreAI::setResponse(std::string const &response)
{
  _response = response;
}

void zappy::CoreAI::setX(size_t x)
{
  _pos.x = x;
}

void zappy::CoreAI::setY(size_t y)
{
  _pos.y = y;
}

zappy::CoreAI::CoreAI()
    : _message(), _response(), _pos(),
      _actions({&zappy::network::SendCommand::forward,
                &zappy::network::SendCommand::turnLeft,
                &zappy::network::SendCommand::turnRight,
                &zappy::network::SendCommand::look,
                &zappy::network::SendCommand::inventory,
                &zappy::network::SendCommand::broadcast,
                &zappy::network::SendCommand::nbrUnusedTeamSlot,
                &zappy::network::SendCommand::fork,
                &zappy::network::SendCommand::eject,
                &zappy::network::SendCommand::takeObj,
                &zappy::network::SendCommand::setObj,
                &zappy::network::SendCommand::incantation,
                &zappy::network::SendCommand::rawcommand})
{
}
