//
// Created by brout_m on 12/06/17.
//

#include "server.h"
#include "server/gui_commands.h"

int gui_mct(t_server *server, ID id, char *cmd)
{
  int i;
  int size;
  int width;

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
