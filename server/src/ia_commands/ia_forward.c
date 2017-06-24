//
// Created by puilla_e on 09/06/17.
//

#include <string.h>
#include "server/server_data.h"

void	move_to_dir(t_server *server, t_client *client, Direction dir)
{
  if (dir == NORTH)
    client->ia.pos.y = client->ia.pos.y == 0 ?
		       (int) server->game.height - 1 : client->ia.pos.y - 1;
  else if (dir == SOUTH)
    client->ia.pos.y = client->ia.pos.y == (int) server->game.height - 1 ?
		       0 : client->ia.pos.y + 1;
  else if (dir == WEST)
    client->ia.pos.x = client->ia.pos.x == 0 ?
		       (int) server->game.width - 1 : client->ia.pos.x - 1;
  else
    client->ia.pos.x = client->ia.pos.x == (int) server->game.width - 1 ?
		       0 : client->ia.pos.x + 1;
}

int	ia_forward(t_server *server, ID id, char *cmd)
{
  //TODO add time management
  (void)cmd;
  move_to_dir(server, &server->game.clients[id], server->game.clients->ia.dir);
  strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
  return (0);
}
