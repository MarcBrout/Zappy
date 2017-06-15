//
// Created by brout_m on 13/06/17.
//

#include <string.h>
#include <stdlib.h>
#include "server/send.h"

static int send_player_inventory(t_server *server, ID id)
{
  int i;
  t_ia *ia;

  i = 0;
  ia = &server->game.clients[id].ia;
  send_to_gui(server, "pin #%d %d %d ", id, ia->pos.x, ia->pos.y);
  while (i < OBJ_COUNT)
  {
    send_to_gui(server, "%d", ia->inventory[i]);
    if (i < OBJ_COUNT - 1)
      send_to_gui(server, " ");
    ++i;
  }
  return (send_to_gui(server, "plv #%d %d\n", id, ia->level));
}

int gui_pin(t_server *server, Socket sock, char *cmd)
{
  char *idstr;
  int id;

  (void)sock;
  strtok(cmd, " ");
  if ((idstr = strtok(NULL, " ")) == NULL)
    return (send_to_gui(server, "suc\n"));
  if (idstr[0] != '#')
    return (send_to_gui(server, "sbp\n"));
  id = atoi(idstr);
  if (find_ID(server, id, true) < 0)
    return (send_to_gui(server, "sbp\n"));
  return (send_player_inventory(server, id));
}