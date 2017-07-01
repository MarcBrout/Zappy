/*
** gui_sst.c for zappy in server/src/id_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:21:23 2017 brout_m
** Last update Wed Jun 28 10:41:27 2017 brout_m
*/
#include <string.h>
#include <stdlib.h>
#include "server.h"

int		gui_sst(t_server *server, ID id, char *cmd)
{
  char		*timestr;
  int		time;

  (void)id;
  strtok(cmd, " ");
  if ((timestr = strtok(NULL, " ")) == NULL)
    return (send_to_gui(server, "sbp\n"));
  time = atoi(timestr);
  if (time < 0 || time >= MAX_TIME)
    return (send_to_gui(server, "sbp\n"));
  log_this("[SST] GUI modified Time unit : %d to %d\n",
	   server->config.time, time);
  server->config.time = (uint16_t)time;
  set_new_timer(server->config.time);
  return (send_to_gui(server, "sgt %d\n", time));
}
