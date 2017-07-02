/*
** logic_broadcast.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:27:50 2017 Edouard
** Last update Sun Jul  2 16:04:11 2017 brout_m
*/

#include <string.h>
#include "server/ia_commands.h"
#include "server/gui_events.h"
#include "server/direction_manager.h"

static int	pos_text(char *cmd)
{
  int 		len;

  len = (int)strlen("Broadcast");
  if (cmd[len] != ' ')
    return (0);
  if (cmd[len] == '\0')
    return (0);
  return (len + 1);
}

int		logic_broadcast(t_server *server, ID id, char *cmd)
{
  ID		cli = 0;
  t_client	*client;
  int 		pos;
  t_client	*tmp;

  pos = pos_text(cmd);
  client = &server->game.clients[id];
  event_pbc(server, id, pos == 0 ? "" : cmd + pos);
  while (cli < server->game.max_slot)
    {
      tmp = &server->game.clients[cli];
      if (tmp->alive == true && tmp->ia.incanting == false && tmp != client)
	{
	  send_to_ia(server, cli,
		     "message %d, %s\n",
		     find_direction(server, &client->ia.pos,
				    &tmp->ia.pos, tmp->ia.dir),
		     pos == 0 ? "" : cmd + pos);
	}
      ++cli;
    }
  strncircular(&client->w, "ok\n", strlen("ok\n"));
  return (0);
}
