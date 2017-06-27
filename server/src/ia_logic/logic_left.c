/*
** logic_left.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:31:32 2017 Edouard
** Last update Tue Jun 27 17:31:38 2017 Edouard
*/

#include <string.h>
#include "server/server_data.h"

int	logic_left(t_server *server, ID id, char *cmd)
{
  //TODO GUI add event ppo
  (void)cmd;
  server->game.clients[id].ia.dir =
   server->game.clients[id].ia.dir == NORTH ? WEST :
   server->game.clients[id].ia.dir - 1;
  strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
  return (0);
}
