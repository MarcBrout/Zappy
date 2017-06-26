/*
** gui_bct.c for zappy in server/src/ia_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:15:36 2017 brout_m
** Last update Sun Jun 25 02:16:20 2017 brout_m
*/
#include <string.h>
#include <stdlib.h>
#include "server.h"

int		send_case_content(t_server *server, uint32_t x, uint32_t y)
{
  int		i;
  uint32_t	pos;

  if (send_to_gui(server, "bct %d %d ", x, y))
    return (1);
  i = 0;
  pos = x + y * server->config.width;
  while (i < OBJ_COUNT)
    {
      send_to_gui(server, "%d", server->game.map[pos].objects[i]);
      if (i < OBJ_COUNT - 1 && send_to_gui(server, " "))
        return (1);
      ++i;
    }
  return (send_to_gui(server, "\n"));
}

int		gui_bct(t_server *server, ID id, char *cmd)
{
  char		*xstr;
  char		*ystr;
  int		x;
  int		y;

  strtok(cmd, " ");
  (void)id;
  if ((xstr = strtok(NULL, " ")) == NULL || (ystr = strtok(NULL, " ")) == NULL)
    return (send_to_gui(server, "suc\n"));
  x = atoi(xstr);
  y = atoi(ystr);
  log_this("[BCT] GUI asked content of cell:\n\tx: %d\n\ty: %d\n", x, y);
  if (x < 0 || x > server->config.width - 1 ||
      y < 0 || y > server->config.height - 1)
    return (send_to_gui(server, "sbp\n"));
  return (send_case_content(server, x, y));
}
