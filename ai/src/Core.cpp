//
// Created by Pierre Bougon on 21/06/17.
//

#include <vector>
#include "network/Client.hpp"
#include "tools/Logger.hpp"
#include "Core.hpp"
#include "core_ai/CoreAI.hpp"
#include "ai_logic/AILogic.hpp"

zappy::Core::Core() : _running(false), _waitingForResponse(0), _ai(std::make_unique<AILogic>(*this))
{
}

zappy::Core::~Core()
{
}

void zappy::Core::run()
{
  std::vector<std::string> servMessages;
  std::string              command;

  _running = true;
  while (_running)
    {
      // check server send
      servMessages = network::Client::getInstance().getServerMessages();
      for (std::vector<std::string>::iterator it = servMessages.begin();
           it < servMessages.end(); ++it)
	manageResponse(*it);
      servMessages.clear();

      // TODO PROCESS IA REPLACE WITH FULL IA PROCESS
      _ai->sendAction(CoreAI::FORWARD);

      if (waitForReponses(1, {"ok"}))
      {
        Logger::log(Logger::_DEBUG_, "forward ok!");
      }

      ::usleep(10);
    }
}

bool zappy::Core::waitForReponses(std::int32_t                    count,
                                  std::vector<std::string> const &anwsers)
{
  std::vector<std::string> servMessages;

  _waitingForResponse = count;
  _ai->resetResponse();
  while (_waitingForResponse > 0 && _running)
    {
      servMessages = network::Client::getInstance().getServerMessages();
      for (std::vector<std::string>::iterator it = servMessages.begin();
           it < servMessages.end() && _running; ++it)
	manageResponse(*it);
      ::usleep(10);
    }
  return (anwsers == _ai->getResponse());
}

void zappy::Core::manageResponse(std::string servMessage)
{
  Logger::log(Logger::_DEBUG_, "command received : " + servMessage);
  if (servMessage == "dead")
    _running = false;
  else if (servMessage.substr(0, servMessage.find(" ")) == "message")
    _ai->setMessage(servMessage);
  else
    {
      --_waitingForResponse;
      _ai->addResponse(servMessage);
    }
}

void zappy::Core::auth(std::string teamName)
{
  bool                     welcome = false;
  bool                     accepted = false;
  bool                     placed = false;
  std::vector<std::string> servMessages;
  int                      nb;

  while (!welcome)
    {
      servMessages = network::Client::getInstance().getServerMessages();
      for (std::vector<std::string>::iterator it = servMessages.begin();
           it < servMessages.end(); ++it)
	{
	  if (*it == "WELCOME")
	    welcome = true;
	}
    }
  network::Client::getInstance().send(teamName);
  while (!accepted && !placed)
    {
      servMessages = network::Client::getInstance().getServerMessages();
      for (std::vector<std::string>::iterator it = servMessages.begin();
           it < servMessages.end(); ++it)
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
		  network::Client::getInstance().send(teamName);
		}
	    }
	  else if (*it != "")
	    {
	      _ai->setX(static_cast<size_t>(
	          std::atoi(it->substr(0, it->find(" ")).c_str())));
	      _ai->setY(static_cast<size_t>(
	          std::atoi(it->substr(it->find(" ") + 1).c_str())));
	      placed = true;
	    }
	}
    }
  Logger::log(Logger::_DEBUG_, "Authentication successful !");
}
