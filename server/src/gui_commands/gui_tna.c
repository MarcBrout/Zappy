//
// Created by brout_m on 12/06/17.
//

#include "server/send.h"

int	gui_tna(t_server *server, ID id, char *cmd)
{
  int	i;
  int	ret;

  (void)cmd;
  (void)id;
  i = 0;
  while (i < server->config.team_count)
    {
      if ((ret = send_to_gui(server, "tna %s\n", server->config.teams[i])))
	return (ret);
    }
  return (0);
}