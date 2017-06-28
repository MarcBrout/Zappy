/*
** gui_msz.c for zappy in server/src/ia_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:17:14 2017 brout_m
** Last update Wed Jun 28 10:40:35 2017 brout_m
*/
#include "server.h"

int gui_msz(t_server *server, ID id, char *cmd)
{
  (void)cmd;
  (void)id;
  log_this("[MSZ] GUI asked map size:\n\tx: %d\n\ty: %d\n",
	   server->config.width, server->config.height);
  return (send_to_gui(server, "msz %d %d\n",
		      server->config.width,
		      server->config.height));
}
