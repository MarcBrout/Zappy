//
// Created by brout_m on 12/06/17.
//

#include <string.h>
#include <stdlib.h>
#include "server/send.h"

int send_case_content(t_server *server, int x, int y)
{
  int i;
  int pos;

  if (send_to_gui(server, "bct %d %d ", x, y))
    return (1);
  i = 0;
  pos = x + y * server->config.width;
  while (i < OBJ_COUNT)
  {
    send_to_gui(server, "%d", server->game.map[pos].objects[i]);
    if (i < OBJ_COUNT - 1)
      send_to_gui(server, " ");
    ++i;
  }
  return (send_to_gui(server, "\n"));
}

int gui_bct(t_server *server, Socket sock, char *cmd)
{
  char *xstr;
  char *ystr;
  int x;
  int y;

  (void)sock;
  strtok(cmd, " ");
  if ((xstr = strtok(NULL, " ")) == NULL || (ystr = strtok(NULL, " ")) == NULL)
    return (send_to_gui(server, "suc\n"));
  x = atoi(xstr);
  y = atoi(ystr);
  if (x < 0 || x > server->config.width - 1 ||
      y < 0 || y > server->config.height - 1)
    return (send_to_gui(server, "sbp\n"));
  return (send_case_content(server, x, y));
}