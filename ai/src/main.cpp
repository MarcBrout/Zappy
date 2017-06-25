#include <exception>
#include <tools/Logger.hpp>
#include <network/Client.hpp>
#include <Core.hpp>

/*
** main.c for ai in /home/pierre/rendu/TEK2/PSU_2016_zappy/ai
**
** Made by PierreBougon
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 21:52:31 2017 PierreBougon
** Last update Sat Jun 10 22:30:54 2017 PierreBougon
*/

int	main(int ac, char **av)
{
    if (ac != 3)
        return 1;
    try
    {
        zappy::network::Client::getInstance().Init(static_cast<uint16_t>(std::atoi(av[1])), av[2]);
        zappy::network::Client::getInstance().connect();
        zappy::network::Client::getInstance().auth("azeazeae");
        zappy::Core core;
        core.run();
    }
    catch (std::exception const &exception)
    {
        Logger::log(Logger::_DEBUG_, exception.what());
    }
    return (0);
}
