/*
** gui_tna.c for zappy in server/src/id_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:21:51 2017 brout_m
** Last update Sun Jun 25 02:21:59 2017 brout_m
*/
#include "server.h"

int	gui_tna(t_server *server, ID id, char *cmd)
{
  int	i;
  int	ret;

  (void)cmd;
  (void)id;
  i = 0;
  log_this("[TNA] GUI asked team names :");
  while (i < server->config.team_count)
    {
      log_this("\n\t%s", server->config.teams[i].name);
      if ((ret = send_to_gui(server,
			     "tna %s\n",
			     server->config.teams[i].name)))
	return (ret);
      ++i;
    }
  log_this("\n");
  return (0);
}
