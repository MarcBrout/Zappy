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

void zappy::CoreAI::resetResponse()
{
  _response.clear();
}

void zappy::CoreAI::setX(size_t x)
{
  _pos.x = x;
}

void zappy::CoreAI::setY(size_t y)
{
  _pos.y = y;
}

zappy::CoreAI::CoreAI(Core &core)
    : _core(core), _message(), _response(), _pos(),
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

void zappy::CoreAI::addResponse(const std::string &string)
{
  _response.push_back(string);
}

std::vector<std::string> const &zappy::CoreAI::getResponse()
{
  return _response;
}

bool zappy::CoreAI::sendActionAndCheckResponse(
    zappy::CoreAI::ACTION action, const std::string &str, std::uint32_t count,
    const std::vector<std::string> &answ)
{
  sendAction(action, str);
  return (_core.waitForReponses(static_cast<std::int32_t >(count), answ));
}
