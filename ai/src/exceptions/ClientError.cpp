//
// Created by Pierre Bougon on 25/04/17.
//

#include "exceptions/ClientError.hpp"

zappy::network::ClientError::ClientError(const std::string &msg) : runtime_error(msg)
{
}

zappy::network::ClientError::ClientError(const char *msg) : runtime_error(msg)
{
}

zappy::network::ClientError::~ClientError() throw()
{
}
