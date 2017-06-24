//
// Created by Pierre Bougon on 23/06/17.
//

#ifndef CLIENTAI_COREAI_HPP_
#define CLIENTAI_COREAI_HPP_

#include <vector>

namespace zappy
{
    class CoreAI
    {
    public:
        void nextAction();
        void sendAction();
        void setMessage(const std::string &string);
        void setResponse(std::string const &basic_string);

    private:
        std::vector<std::string>    _message;
        std::string                 _response;
    };
}


#endif // !CLIENTAI_COREAI_HPP_
