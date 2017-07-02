/*
** gui_unknown.c for zappy in server/src/ia_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:23:00 2017 brout_m
** Last update Sun Jul  2 15:47:42 2017 Edouard
*/

#include "server.h"

int	gui_unknown(t_server *server, ID id, char *cmd)
{
  (void)id;
  (void)cmd;
  log_this("GUI send unknown command\n");
  return (send_to_gui(server, "suc\n"));
}
