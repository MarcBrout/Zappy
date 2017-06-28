/*
** set_gui.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:52:49 2017 brout_m
** Last update Sun Jun 25 02:52:56 2017 brout_m
*/
#include <stdio.h>
#include <sys/socket.h>
#include "server.h"

int	set_gui(t_server *server,
		fd_set *fds_read,
		fd_set *fds_write)
{
  int	max;

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
