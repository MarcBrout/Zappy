//
// Created by brout_m on 09/06/17.
//

#include <string.h>
#include <stdio.h>
#include "server/gui_commands.h"
#include "server/ia_commands.h"
#include "server.h"

static const t_command gui_commands[GUI_END + 1] =
    {
        {"msz", 3, gui_msz},
        {"bct", 3, gui_bct},
        {"mct", 3, gui_mct},
        {"tna", 3, gui_tna},
        {"ppo", 3, gui_ppo},
        {"plv", 3, gui_plv},
        {"pin", 3, gui_pin},
        {"sgt", 3, gui_sgt},
        {"sst", 3, gui_sst},
        {"unknown", 7, gui_unknown}
    };

static const t_command ia_commands[IA_END + 1] =
    {
        {"Forward", 7, ia_forward},
        {"Right", 5, ia_right},
        {"Left", 4, ia_left},
        {"Look", 4, ia_look},
        {"Inventory", 9, ia_inventory},
        {"Broadcast", 9, ia_broadcast},
        {"Connect_nbr", 11, ia_connect_nbr},
        {"Fork", 4, ia_fork},
        {"Eject", 5, ia_eject},
        {"Take", 4, ia_take},
        {"Set", 3, ia_set},
        {"Incantation", 11, ia_incantation},
        {"unknown", 7, ia_unknown}
    };

static int run(t_server *server, t_client *client, const t_command *commands, size_t size)
{
  char cmd[MESSAGE_MAX_SIZE];
  size_t i;

  i = 0;
  strfromcircular(&client->r, cmd);
  printf("raw cmd :%s:\n", cmd);
  while (i < size)
  {
    if (!strncmp(commands[i].cmd, cmd, commands[i].len) &&
        commands[i].exec(server, client->sock, cmd))
      return (1);
    ++i;
  }
  if (i == size)
    return (commands[size].exec(server, client->sock, cmd));
  return (0);
}

int  proceed_commands(t_server *server)
{
  int i;

  while (find_command(&server->gui.r))
    {
      if (run(server, &server->gui, gui_commands, GUI_END))
      	return (1);
    }
  i = 0;
  while (i < server->config.max_player * server->config.team_count)
  {
    while (find_command(&server->game.clients[i].r))
      {
	if (run(server, &server->game.clients[i], ia_commands, IA_END))
	  return (1);
      }
    ++i;
  }
  return (0);
}

int proceed(t_server *server,
                fd_set *fds_read, fd_set *fds_write)
{
  return (proceed_reads(server, fds_read) ||
          proceed_commands(server) ||
          proceed_writes(server, fds_write));
}