//
// Created by Pierre Bougon on 23/06/17.
//

#ifndef CLIENTAI_COREAI_HPP_
#define CLIENTAI_COREAI_HPP_

#include <vector>
#include <tools/Vector2.hpp>

namespace zappy
{
    class CoreAI
    {
    public:
      virtual ~CoreAI(){};
        void nextAction();
        void sendAction();
        void setMessage(const std::string &string);
        void setResponse(std::string const &basic_string);

        void setX(size_t x);
        void setY(size_t y);

    protected:
        std::vector<std::string>    _message;
        std::string                 _response;
        Vector2s                    _pos;
    };
}


#endif // !CLIENTAI_COREAI_HPP_
