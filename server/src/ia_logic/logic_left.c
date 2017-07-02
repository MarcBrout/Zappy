/*
** logic_left.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:31:32 2017 Edouard
** Last update Sun Jul  2 16:06:55 2017 brout_m
*/

#include <string.h>
#include "server/gui_commands.h"

int	logic_left(t_server *server, ID id, char *cmd)
{
  (void)cmd;
  server->game.clients[id].ia.dir =
    server->game.clients[id].ia.dir == NORTH ? WEST :
    server->game.clients[id].ia.dir - 1;
  send_player_position(server, id);
  strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
  return (0);
}
