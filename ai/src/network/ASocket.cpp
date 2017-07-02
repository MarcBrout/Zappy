//
// Created by Pierre Bougon on 20/04/17.
//

#include <unistd.h>
#include <cstring>
#include <iostream>
#include "exceptions/SocketError.hpp"
#include "tools/Logger.hpp"
#include "network/ASocket.hpp"

zappy::network::ASocket::ASocket(uint16_t port, const std::string &hostname)
    : _socket(-1), _port(port), _hostname(hostname), _servAddr(),
      _server(nullptr)
{
  if (_port == 0)
    _port = 4242;
  init();
}

void zappy::network::ASocket::init()
{
  std::memset((char *)&_servAddr, 0, sizeof(_servAddr));
  _socket = ::socket(AF_INET, SOCK_STREAM, 0);
  if (_socket < 0)
    throw network::SocketError("Cannot create socket");
  _servAddr.sin_family = AF_INET;
  _servAddr.sin_port = htons(_port);
  _servAddr.sin_addr.s_addr = INADDR_ANY;
}

zappy::network::sock_t zappy::network::ASocket::getSocket() const
{
  return _socket;
}

uint16_t zappy::network::ASocket::getPort() const
{
  return _port;
}

const std::string &zappy::network::ASocket::getHostname() const
{
  return _hostname;
}

zappy::network::ASocket::~ASocket()
{
  if (_socket >= 0)
    close(_socket);
}
