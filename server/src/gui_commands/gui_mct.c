/*
** gui_mct.c for zappy in server/src/ia_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:16:26 2017 brout_m
** Last update Sun Jul  2 15:43:16 2017 Edouard
*/

#include "server.h"
#include "server/gui_commands.h"

int	gui_mct(t_server *server, ID id, char *cmd)
{
  int	i;
  int	size;
  int	width;

  i = 0;
  width = server->config.width;
  size = width * server->config.height;
  (void)cmd;
  (void)id;
  log_this("[MCT] GUI asked map content\n");
  while (i < size)
    {
      if (send_case_content(server, i % width, i / width))
	return (1);
      ++i;
    }
  return (0);
}
