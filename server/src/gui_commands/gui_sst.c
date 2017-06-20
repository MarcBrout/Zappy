//
// Created by brout_m on 13/06/17.
//

#include <string.h>
#include <stdlib.h>
#include "server/send.h"

int gui_sst(t_server *server, ID id_gui, char *cmd)
{
  char *timestr;
  int time;

  (void)id_gui;
  strtok(cmd, " ");
  if ((timestr = strtok(NULL, " ")) == NULL)
    return (send_to_gui(server, "sbp\n"));
  time = atoi(timestr);
  if (time < 0 || time > 255)
    return (send_to_gui(server, "sbp\n"));
  server->config.time = (uint8_t)time;
  return (send_to_gui(server, "sgt %d\n", time));
}