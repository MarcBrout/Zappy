//
// Created by brout_m on 01/07/17.
//

#include "server.h"

int proceed_gui_reads(t_server *server, fd_set *fds_read)
{
  if (FD_ISSET(server->gui.sock, fds_read))
    return read_gui(&server->gui, server->gui.sock);
  return (0);
}


int proceed_gui_writes(t_server *server, fd_set *fds_write)
{
  if (FD_ISSET(server->gui.sock, fds_write))
    {
      log_this("Sending commands to GUI\n");
      return (write_client(&server->gui, server->gui.sock));
    }
  return (0);
}
