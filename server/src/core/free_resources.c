/*
** free_resources.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed Jun 28 10:29:37 2017 brout_m
** Last update Wed Jun 28 10:30:08 2017 brout_m
*/
#include <stdlib.h>
#include "server.h"

void		free_resources(t_server *server)
{
  int		i = 0;

  while (i < server->config.team_count)
    {
      free(server->config.teams[i].name);
      ++i;
    }
  free(server->config.teams);
  free(server->game.clients);
  free_eggs(server);
}
