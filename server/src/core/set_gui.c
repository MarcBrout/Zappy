//
// Created by brout_m on 09/06/17.
//

#include <sys/socket.h>
#include "server/server_data.h"

int set_gui(t_server *server,
                   fd_set *fds_read,
                   fd_set *fds_write)
{
  int max;

  max = 0;
  if (!server->gui.alive)
  {
    FD_SET(server->gui_sock, fds_read);
    max = server->gui_sock > max ? server->gui_sock : max;
  }
  else
  {
    FD_SET(server->gui.sock, fds_read);
    if (find_command(&server->gui.w))
      FD_SET(server->gui.sock, fds_write);
    max = server->gui.sock > max ? server->gui.sock : max;
  }
  return (max);
}