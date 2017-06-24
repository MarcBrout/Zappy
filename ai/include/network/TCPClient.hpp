//
// Created by Pierre Bougon on 20/04/17.
//

#ifndef CPP_ZAPPY_TCPCLIENT_HPP_
#define CPP_ZAPPY_TCPCLIENT_HPP_


#include <mutex>
#include <thread>
#include <atomic>
#include "ASocket.hpp"

namespace zappy
{
    namespace network
    {
        class TCPClient : public ASocket
        {
        public:
            TCPClient(uint16_t port, const std::string &hostname);
            virtual ~TCPClient();

            void            connect();
            void            disconnect();
            bool            isConnected();

            void                        send(const std::string &data, sock_t socket) override;
            std::vector<std::string>    receive(sock_t socket) override;

        private:
            std::vector<std::string>    splitReceived();
            void                        manageBuffer(char const *buffer);

        private:
            char            buf[BUFFER_SIZE];
            size_t          head;
            size_t          tail;

        };
    }
}


#endif // !CPP_ZAPPY_TCPCLIENT_HPP_
