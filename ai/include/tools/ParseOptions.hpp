//
// Created by Pierre Bougon on 26/06/17.
//

#ifndef CLIENTAI_PARSEOPTIONS_HPP_
#define CLIENTAI_PARSEOPTIONS_HPP_

#include <string>

namespace zappy
{
    class ParseOptions
    {
    public:
        ParseOptions();
        ~ParseOptions();

        void parse(int ac, char **av);

        const std::string   &getTeamName() const;
        const std::string   &getServName() const;
        uint16_t            getPort() const;

    private:
        std::string     _teamName;
        std::string     _servName;
        uint16_t        _port;
    };
}


#endif // !CLIENTAI_PARSEOPTIONS_HPP_
