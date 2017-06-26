//
// Created by Pierre Bougon on 21/06/17.
//

#ifndef CLIENTAI_CORE_HPP_
#define CLIENTAI_CORE_HPP_


#include <ai_logic/AILogic.hpp>

namespace zappy
{
    class Core
    {
    public:
        Core();
        Core(Core const &other) = delete;
        ~Core();

        Core &operator=(Core const &other) = delete;

        void run();
        void auth(std::string teamName);

    private:
        void manageResponse(std::string servMessage);

    private:
        bool    _running;
        bool    _waitingForResponse;
        AILogic _ai;
    };
}


#endif // !CLIENTAI_CORE_HPP_
