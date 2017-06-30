/*
** ia_incantation.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:35:08 2017 Edouard
** Last update Tue Jun 27 17:39:07 2017 Edouard
*/

#include <string.h>
#include "server/ia_commands.h"

bool		is_incantation(t_server *server, t_position *pos)
{
  t_client	*client;
  int 		cli = 0;

  while (cli < server->game.max_slot)
    {
      client = &server->game.clients[cli];
      if (client->alive &&
	  client->ia.pos.x == pos->x &&
	  client->ia.pos.y == pos->y &&
	  client->store.commands != NULL &&
	  strcmp(client->store.commands->command, "Incantation") == 0)
	return (true);
    }
  return (false);
}


int	ia_incantation(t_server *server, ID id, char *cmd)
{
  (void) cmd;
  return (store_command(&server->game.clients[id].store,
			"IncantationStart",
			0));
}
