/*
** gui_welcome.c for zappy in server/src/gui_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Jun 27 01:39:05 2017 brout_m
** Last update Wed Jun 28 10:42:00 2017 brout_m
*/
#include <string.h>
#include <unistd.h>
#include "server.h"
#include "server/gui_commands.h"

int gui_welcome(t_server *server, ID id, char *cmd)
{
  (void)cmd;
  if (!server->gui.active)
    {
      memcpy(&server->gui, &server->game.clients[id], sizeof(t_client));
      set_gui_connected(true, true);
      send_informations(server);
      log_this("Gui connected Correctly\n");
      memset(&server->game.clients[id], 0, sizeof(t_client));
    }
  else
    {
      send_to_ia(server, id,
		 "smg GUI already connected, closing off socket\n");
      server->game.clients[id].died = true;
    }
  return (0);
}
