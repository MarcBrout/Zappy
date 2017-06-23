//
// Created by brout_m on 12/06/17.
//

#include "server/gui_commands.h"

int gui_mct(t_server *server, Socket sock, char *cmd)
{
  int i;
  int size;
  int width;

  i = 0;
  width = server->config.width;
  size = width * server->config.height;
  (void)cmd;
  (void)sock;
  while (i < size)
  {
    if (send_case_content(server, i % width, i / width))
      return (1);
    ++i;
  }
  return (0);
}