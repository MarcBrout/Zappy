//
// Created by brout_m on 13/06/17.
//

#include <string.h>
#include <stdlib.h>
#include "server/send.h"

static int send_player_position(t_server *server, ID id)
{
  t_ia *ia;

  ia = &server->game.clients[id].ia;
  return (send_to_gui(server, "ppo #%d %d %d %d\n",
                      id, ia->pos.x, ia->pos.y, ia->dir));
}

int gui_ppo(t_server *server, ID id_gui, char *cmd)
{
  char *idstr;
  int id;

  (void)id_gui;
  strtok(cmd, " ");
  if ((idstr = strtok(NULL, " ")) == NULL)
    return (send_to_gui(server, "suc\n"));
  if (idstr[0] != '#')
    return (send_to_gui(server, "sbp\n"));
  id = atoi(idstr);
  if (find_ID(server, id, true) < 0)
    return (send_to_gui(server, "sbp\n"));
  return (send_player_position(server, id));
}
