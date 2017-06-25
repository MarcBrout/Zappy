//
// Created by Pierre Bougon on 20/04/17.
//

#ifndef CPP_ZAPPY_CLIENT_HPP_
#define CPP_ZAPPY_CLIENT_HPP_


#include <thread>
#include <mutex>
#include "network/TCPClient.hpp"
#include "tools/Singleton.hpp"
#include "tools/FDManager.hpp"

namespace zappy
{
    namespace network
    {
        class Client : public TCPClient, public Singleton<Client>
        {
        private:
            friend class Singleton<Client>;
            Client(uint16_t port, const std::string &hostname);
            Client(Client const &other) = delete;
            Client &operator=(Client const &other) = delete;
            Client();

        public:
            // Use this method as the constructor
            void Init(uint16_t port, std::string const &host);
            std::vector<std::string> getServerMessages();
            virtual ~Client();
            void auth(std::string teamName);

        private:

        private:
            FDManager   _fdManager;
        };
    }
}

#endif // !CPP_ZAPPY_CLIENT_HPP_
