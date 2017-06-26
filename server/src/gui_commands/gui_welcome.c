/*
** gui_welcome.c for zappy in server/src/gui_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Jun 27 01:39:05 2017 brout_m
** Last update Tue Jun 27 01:39:38 2017 brout_m
*/
#include "server.h"
#include "server/gui_commands.h"

int gui_welcome(t_server *server, ID id, char *cmd)
{
  (void)server;
  (void)id;
  (void)cmd;
  set_gui_connected(true, true);
  log_this("Gui connected Correctly\n");
  return (0);
}
