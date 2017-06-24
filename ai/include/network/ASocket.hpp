//
// Created by Pierre Bougon on 20/04/17.
//

#ifndef CPP_ZAPPY_ASOCKET_HPP_
#define CPP_ZAPPY_ASOCKET_HPP_


#include <netinet/in.h>
#include <string>
#include <netdb.h>
#include <vector>

namespace zappy
{
    namespace network
    {
        typedef int sock_t;

        class ASocket
        {
        public:
            static constexpr size_t BUFFER_SIZE = 4096;
            static constexpr char END_OF_COMMAND = '\n';

        public:
            ASocket(uint16_t _port, const std::string &_hostname);
            ASocket(const ASocket &other) = delete;
            ASocket() = delete;

            virtual ~ASocket();

            ASocket &operator=(ASocket const &other) = delete;

            sock_t              getSocket() const;
            uint16_t            getPort() const;
            const std::string   &getHostname() const;

            virtual void                        send(const std::string &data, sock_t socket) = 0;
            virtual std::vector<std::string>    receive(sock_t socket) = 0;

        protected:
            sock_t          _socket;
            uint16_t        _port;
            std::string     _hostname;
            sockaddr_in     _servAddr;
            hostent         *_server;

        protected:
            void init();
        };
    }
}


#endif // !CPP_ZAPPY_ASOCKET_HPP_
