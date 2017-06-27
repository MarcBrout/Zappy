/*
** logic_broadcast.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:27:50 2017 Edouard
** Last update Tue Jun 27 17:27:57 2017 Edouard
*/

#include <string.h>
#include "server/gui_events.h"
#include "server/direction_manager.h"

int		logic_broadcast(t_server *server, ID id, char *cmd)
{
  char 		*text;
  ID		cli;
  t_client	*client;

  strtok(cmd, " ");
  cli = 0;
  client = &server->game.clients[id];
  text = strtok(NULL, " ");
  event_pbc(server, id, text);
  while (cli < server->game.max_slot)
    {
      if (server->game.clients[cli].alive == true &&
	  &server->game.clients[cli] != client)
	{
	  send_to_ia(server, server->game.clients[cli].sock,
		     "message %d, %s\n",
		     find_direction(server,
				    &client->ia.pos,
				    &server->game.clients[cli].ia.pos,
				    server->game.clients[cli].ia.dir),
		     text == NULL ? "" : text);
	}
      ++cli;
    }
  strncircular(&client->w, "ok\n", strlen("ok\n"));
  return (0);
}
