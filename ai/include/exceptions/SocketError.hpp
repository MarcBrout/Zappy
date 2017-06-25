//
// Created by Pierre Bougon on 22/04/17.
//

#ifndef CPP_ZAPPY_SOCKETERROR_HPP_
#define CPP_ZAPPY_SOCKETERROR_HPP_


#include <stdexcept>

namespace zappy
{
    namespace network
    {
        class SocketError : public std::runtime_error
        {
        public:
            SocketError(const std::string &msg);
            SocketError(const char *msg);

            virtual ~SocketError() throw();
        };
    }
}


#endif // !CPP_ZAPPY_SOCKETERROR_HPP_
