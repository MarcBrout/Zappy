//
// Created by brout_m on 13/06/17.
//

#include <string.h>
#include <stdlib.h>
#include "server.h"

static int send_player_position(t_server *server, ID id)
{
  t_ia *ia;

  ia = &server->game.clients[id].ia;
  log_this("[PPO] GUI asked for Client '%d' position on:"
               "\n\tx: %d\n\ty: %d\n\tdir: %d\n ", id,
           ia->pos.x, ia->pos.y, ia->dir);
  return (send_to_gui(server, "ppo #%d %d %d %d\n",
                      id, ia->pos.x, ia->pos.y, ia->dir));
}

int gui_ppo(t_server *server, Socket sock, char *cmd)
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
  return (send_player_position(server, id));
}
