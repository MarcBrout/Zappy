/*
** gui_sgt.c for zappy in server/src/id_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:20:55 2017 brout_m
** Last update Sun Jun 25 02:22:24 2017 brout_m
*/
#include "server.h"

int	gui_sgt(t_server *server, ID id, char *cmd)
{
  (void)cmd;
  (void)id;
  log_this("[SGT] GUI asked Time unit : %d\n", server->config.time);
  return (send_to_gui(server, "sgt %d\n", server->config.time));
}
