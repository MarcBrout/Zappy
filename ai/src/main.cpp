#include <exception>
#include <tools/Logger.hpp>
#include <network/Client.hpp>
#include <Core.hpp>
#include <tools/ParseOptions.hpp>

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
    std::srand(static_cast<std::uint32_t >(std::time(0) * getpid()));
    try
    {
        zappy::ParseOptions parseOptions;
        parseOptions.parse(ac, av);

        zappy::network::Client::getInstance().Init(parseOptions.getPort(), parseOptions.getServName());
        zappy::network::Client::getInstance().connect();
        zappy::Core core;
        core.auth(parseOptions.getTeamName());
        core.run();
    }
    catch (std::exception const &exception)
    {
        Logger::log(Logger::ERROR, exception.what());
    }
    return (0);
}
