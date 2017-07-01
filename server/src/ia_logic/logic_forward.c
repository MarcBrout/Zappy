/*
** logic_forward.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:29:56 2017 Edouard
** Last update Tue Jun 27 17:30:02 2017 Edouard
*/

#include <string.h>
#include "server/gui_commands.h"

void	forward_pos(t_server *server, t_position *pos, Direction dir, int nb)
{
  int 	i;

  i = 0;
  while (i < nb)
    {
      if (dir == NORTH)
	pos->y = pos->y == 0 ?
		 (int) server->game.height - 1 : pos->y - 1;
      else if (dir == SOUTH)
	pos->y = pos->y == (int) server->game.height - 1 ?
		 0 : pos->y + 1;
      else if (dir == WEST)
	pos->x = pos->x == 0 ?
		 (int) server->game.width - 1 : pos->x - 1;
      else
	pos->x = pos->x == (int) server->game.width - 1 ?
		 0 : pos->x + 1;
      ++i;
    }
}

int	logic_forward(t_server *server, ID id, char *cmd)
{
  (void)cmd;
  forward_pos(server,
	      &server->game.clients[id].ia.pos,
	      server->game.clients[id].ia.dir,
	      1);
  send_player_position(server, id);
  strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
  return (0);
}
