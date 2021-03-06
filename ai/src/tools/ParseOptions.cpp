//
// Created by Pierre Bougon on 26/06/17.
//

#include <getopt.h>
#include <iostream>
#include "tools/ParseOptions.hpp"

zappy::ParseOptions::ParseOptions()
        : _teamName(""), _servName(""), _port(0)
{}

zappy::ParseOptions::~ParseOptions()
{}

void zappy::ParseOptions::parse(int ac, char **av)
{
    int opt;

    while ((opt = ::getopt(ac, av, "n:p:h:")) != -1)
    {
        switch (opt)
        {
            case 'n':
            {
                _teamName = optarg;
                break;
            }
            case 'p':
            {
                _port = static_cast<uint16_t>(atoi(optarg));
                break;
            }
            case 'h':
            {
                _servName = optarg;
                break;
            }
            default:
            {
                exit(EXIT_FAILURE);
            }
        }
    }
}

const std::string &zappy::ParseOptions::getTeamName() const
{
    return _teamName;
}

const std::string &zappy::ParseOptions::getServName()
{
    if (_servName == "")
        _servName = "127.0.0.1";
    return _servName;
}

uint16_t zappy::ParseOptions::getPort()
{
    if (_port == 0)
        _port = 4242;
    return _port;
}
