//
// Created by brout_m on 13/06/17.
//
#include <string.h>
#include <stdlib.h>
#include "server.h"

static int send_player_lvl(t_server *server, ID id)
{
  t_ia *ia;

  ia = &server->game.clients[id].ia;
  return (send_to_gui(server, "plv #%d %d\n", id, ia->level));
}

int gui_plv(t_server *server, Socket sock, char *cmd)
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
  log_this("[PLV] GUI asked for Client '%d' level\n", id);
  return (send_player_lvl(server, id));
}