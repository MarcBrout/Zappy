/*
** proceed_gui.c for zappy  in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jul  2 15:50:29 2017 brout_m
** Last update Sun Jul  2 16:17:59 2017 brout_m
*/
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
      return (write_client(server, &server->gui, server->gui.sock));
    }
  return (0);
}
