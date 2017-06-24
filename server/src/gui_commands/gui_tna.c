//
// Created by brout_m on 12/06/17.
//

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
      log_this("\n\t%s", server->config.teams[i]);
      if ((ret = send_to_gui(server, "tna %s\n", server->config.teams[i])))
	return (ret);
    }
  log_this("\n");
  return (0);
}