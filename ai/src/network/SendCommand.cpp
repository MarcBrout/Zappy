//
// Created by Pierre Bougon on 21/06/17.
//

#include "network/SendCommand.hpp"
#include "network/Client.hpp"

void zappy::network::SendCommand::forward(const std::string &)
{
  network::Client::getInstance().send("Forward");
}

void zappy::network::SendCommand::turnLeft(const std::string &)
{
  network::Client::getInstance().send("Left");
}

void zappy::network::SendCommand::turnRight(const std::string &)
{
  network::Client::getInstance().send("Right");
}

void zappy::network::SendCommand::look(const std::string &)
{
  network::Client::getInstance().send("Look");
}

void zappy::network::SendCommand::inventory(const std::string &)
{
  network::Client::getInstance().send("Inventory");
}

void zappy::network::SendCommand::broadcast(const std::string &txt)
{
  network::Client::getInstance().send("Broadcast " + txt);
}

void zappy::network::SendCommand::nbrUnusedTeamSlot(const std::string &)
{
  network::Client::getInstance().send("Connect_nbr");
}

void zappy::network::SendCommand::fork(const std::string &)
{
  network::Client::getInstance().send("Fork");
}

void zappy::network::SendCommand::eject(const std::string &)
{
  network::Client::getInstance().send("Eject");
}

void zappy::network::SendCommand::takeObj(const std::string &obj)
{
  network::Client::getInstance().send("Take " + obj);
}

void zappy::network::SendCommand::setObj(const std::string &obj)
{
  network::Client::getInstance().send("Set " + obj);
}

void zappy::network::SendCommand::incantation(const std::string &)
{
  network::Client::getInstance().send("Incantation");
}

void zappy::network::SendCommand::rawcommand(const std::string &cmd)
{
  network::Client::getInstance().send(cmd);
}