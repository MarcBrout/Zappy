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
            static void forward();
            static void turnLeft();
            static void turnRight();
            static void look();
            static void inventory();
            static void broadcast();
            static void nbrUnusedTeamSlot();
            static void fork();
            static void eject();
            static void takeObj();
            static void setObj();
            static void incantation();
        };
    }
}

#endif // !CLIENTAI_COMMAND_HPP_
