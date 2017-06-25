//
// Created by Pierre Bougon on 25/04/17.
//

#ifndef CPP_ZAPPY_CLIENTERROR_HPP_
#define CPP_ZAPPY_CLIENTERROR_HPP_


#include <stdexcept>

namespace zappy
{
    namespace network
    {
        class ClientError : public std::runtime_error
        {
        public:
            ClientError(const std::string &msg);
            ClientError(const char *msg);

            virtual ~ClientError() throw();

        };
    }
}

#endif // !CPP_ZAPPY_CLIENTERROR_HPP_
