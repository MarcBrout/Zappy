//
// Created by Pierre Bougon on 25/04/17.
//

#ifndef CPP_INDIE_CLIENTERROR_HPP_
#define CPP_INDIE_CLIENTERROR_HPP_


#include <stdexcept>

namespace zappy
{
    namespace network
    {
        class ClientError : public std::runtime_error
        {
            ClientError(const std::string &msg);
            ClientError(const char *msg);

            virtual ~ClientError() throw();

        };
    }
}


#endif // !CPP_INDIE_CLIENTERROR_HPP_
