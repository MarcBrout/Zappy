/*
** proceed_gui.c for proceed_gui in /home/duhieu_b/PSU/PSU_2016_zappy
**
** Made by duhieu_b
** Login   <benjamin.duhieu@epitech.eu>
**
** Started on  Sat Jul  1 16:01:10 2017 duhieu_b
** Last update Sat Jul  1 16:01:31 2017 duhieu_b
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
      return (write_client(&server->gui, server->gui.sock));
    }
  return (0);
}
