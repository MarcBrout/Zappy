//
// Created by Pierre Bougon on 20/04/17.
//

#ifndef CPP_INDIE_TCPCLIENT_HPP_
#define CPP_INDIE_TCPCLIENT_HPP_


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

            void            send(const std::string &data, sock_t socket = _socket) override;
            std::string     receive(sock_t socket = _socket) override;

        private:

        };
    }
}


#endif // !CPP_INDIE_TCPCLIENT_HPP_
