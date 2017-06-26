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
                //TODO err
                std::cerr << "NOPE" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

const std::string &zappy::ParseOptions::getTeamName() const
{
    return _teamName;
}

const std::string &zappy::ParseOptions::getServName() const
{
    return _servName;
}

uint16_t zappy::ParseOptions::getPort() const
{
    return _port;
}
