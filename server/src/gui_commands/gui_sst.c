//
// Created by brout_m on 13/06/17.
//

#include <string.h>
#include <stdlib.h>
#include "server.h"

int gui_sst(t_server *server, t_client *client, char *cmd)
{
  char *timestr;
  int   time;

  (void)client;
  strtok(cmd, " ");
  if ((timestr = strtok(NULL, " ")) == NULL)
    return (send_to_gui(server, "sbp\n"));
  time = atoi(timestr);
  if (time < 0 || time >= MAX_TIME)
    return (send_to_gui(server, "sbp\n"));
  log_this("[SST] GUI modified Time unit : %d to %d\n",
           server->config.time, time);
  server->config.time = (uint16_t)time;
  return (send_to_gui(server, "sgt %d\n", time));
}