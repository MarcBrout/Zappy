/*
** logic_broadcast.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:27:50 2017 Edouard
** Last update Tue Jun 27 18:21:56 2017 brout_m
*/

#include <string.h>
#include <server/ia_commands.h>
#include "server/gui_events.h"
#include "server/direction_manager.h"

static void	extract_text(char *cmd, char *buf)
{
  int 		len;
  int 		i;

  memset(buf, 0, BUFFER_MAX_SIZE);
  len = (int) strlen("Broadcast");
  if (cmd[len] != ' ')
    return ;
  if (cmd[len] == '\0')
    return ;
  len = len + 1;
  i = 0;
  while (cmd[i + len] != '\0')
    {
      buf[i] = cmd[len + i];
      ++i;
    }
}

int		logic_broadcast(t_server *server, ID id, char *cmd)
{
  ID		cli = 0;
  t_client	*client;
  char		buf[BUFFER_MAX_SIZE];

  extract_text(cmd, buf);
  client = &server->game.clients[id];
  event_pbc(server, id, buf);
  while (cli < server->game.max_slot)
    {
      if (server->game.clients[cli].alive == true &&
          server->game.clients[cli].ia.incanting == false &&
	  &server->game.clients[cli] != client)
	{
	  send_to_ia(server, cli,
		     "message %d, %s\n",
		     find_direction(server,
				    &client->ia.pos,
				    &server->game.clients[cli].ia.pos,
				    server->game.clients[cli].ia.dir), buf);
	}
      ++cli;
    }
  strncircular(&client->w, "ok\n", strlen("ok\n"));
  return (0);
}
