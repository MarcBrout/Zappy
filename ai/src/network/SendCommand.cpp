//
// Created by Pierre Bougon on 21/06/17.
//

#include <network/SendCommand.hpp>
#include <network/Client.hpp>

void zappy::network::SendCommand::forward()
{
    network::Client::getInstance().send("Forward");
}

void zappy::network::SendCommand::turnLeft()
{
    network::Client::getInstance().send("Left");
}

void zappy::network::SendCommand::turnRight()
{
    network::Client::getInstance().send("Right");
}

void zappy::network::SendCommand::look()
{
    network::Client::getInstance().send("Look");
}

void zappy::network::SendCommand::inventory()
{
    network::Client::getInstance().send("Inventory");
}

void zappy::network::SendCommand::broadcast()
{
    network::Client::getInstance().send("Broadcast text");
}

void zappy::network::SendCommand::nbrUnusedTeamSlot()
{
    network::Client::getInstance().send("Connect_nbr");
}

void zappy::network::SendCommand::fork()
{
    network::Client::getInstance().send("Fork");
}

void zappy::network::SendCommand::eject()
{
    network::Client::getInstance().send("Eject");
}

void zappy::network::SendCommand::takeObj()
{
    network::Client::getInstance().send("Take object");
}

void zappy::network::SendCommand::setObj()
{
    network::Client::getInstance().send("Set object");
}

void zappy::network::SendCommand::incantation()
{
    network::Client::getInstance().send("Incantation");
}
