//
// Created by Pierre Bougon on 21/06/17.
//

#ifndef CLIENTAI_COMMAND_HPP_
#define CLIENTAI_COMMAND_HPP_

#include <string>

namespace zappy
{
  namespace network
  {
    class SendCommand
    {
    public:
      static void forward(const std::string &);
      static void turnLeft(const std::string &);
      static void turnRight(const std::string &);
      static void look(const std::string &);
      static void inventory(const std::string &);
      static void broadcast(const std::string &);
      static void nbrUnusedTeamSlot(const std::string &);
      static void fork(const std::string &);
      static void eject(const std::string &);
      static void takeObj(const std::string &);
      static void setObj(const std::string &);
      static void incantation(const std::string &);
      static void rawcommand(const std::string &);
    };
  }
}

#endif // !CLIENTAI_COMMAND_HPP_
