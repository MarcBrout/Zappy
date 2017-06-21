//
// Created by Pierre Bougon on 20/04/17.
//

#ifndef CPP_INDIE_CLIENT_HPP_
#define CPP_INDIE_CLIENT_HPP_


#include <thread>
#include <mutex>
#include "network/TCPClient.hpp"
#include "tools/Singleton.hpp"

namespace zappy
{
    namespace network
    {
        class Client : public TCPClient, public Singleton<Client>
        {
            friend class Singleton<Client>;
        private:
            Client(uint16_t port, const std::string &hostname);
            Client(Client const &other) = delete;
            Client &operator=(Client const &other) = delete;
            Client();

        public:
            // Use this method as the constructor
            void Init(uint16_t port, std::string const &host);
            virtual ~Client();
        };
    }
}

#endif // !CPP_INDIE_CLIENT_HPP_
