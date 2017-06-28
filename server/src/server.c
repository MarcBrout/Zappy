/*
** server.c for zappy in server/src
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 17:02:40 2017 brout_m
** Last update Sat Jun 24 17:03:16 2017 brout_m
*/
#include <stdlib.h>
#include <string.h>
#include "server.h"

int		main(int ac, char **av)
{
  t_server	server;

  memset(&server, 0, sizeof(server));
  log_this("Server started, parsing arguments...\n");
  if (process_command_line(&server.config, ac, av) ||
      launch_server(&server))
    return (84);
  return (EXIT_SUCCESS);
}
