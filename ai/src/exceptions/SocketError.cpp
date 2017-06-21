//
// Created by Pierre Bougon on 22/04/17.
//

#include <netinet/in.h>
#include "exceptions/SocketError.hpp"

zappy::network::SocketError::SocketError(const std::string &msg) : runtime_error(msg)
{}

zappy::network::SocketError::SocketError(const char *msg) : runtime_error(msg)
{
}

zappy::network::SocketError::~SocketError() throw()
{
}
