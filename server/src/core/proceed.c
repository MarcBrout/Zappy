//
// Created by brout_m on 09/06/17.
//

#include <string.h>
#include "server/gui_commands.h"
#include "server/ia_commands.h"
#include "server.h"

static const t_command gui_commands[GUI_END + 1] =
    {
        {"msz", 3, gui_unknown},
        {"bct", 3, gui_unknown},
        {"mct", 3, gui_unknown},
        {"tna", 3, gui_unknown},
        {"ppo", 3, gui_unknown},
        {"plv", 3, gui_unknown},
        {"pin", 3, gui_unknown},
        {"sgt", 3, gui_unknown},
        {"ssi", 3, gui_unknown},
        {"unknown", 7, gui_unknown}
    };

static const t_command ia_commands[IA_END + 1] =
    {
        {"Advance", 7, ia_unknown},
        {"Right", 7, ia_unknown},
        {"Left", 7, ia_unknown},
        {"See", 7, ia_unknown},
        {"Inventory", 7, ia_unknown},
        {"Broadcast", 7, ia_unknown},
        {"Connect_nbr", 7, ia_unknown},
        {"Fork", 7, ia_unknown},
        {"Eject", 7, ia_unknown},
        {"Take", 7, ia_unknown},
        {"Set", 7, ia_unknown},
        {"Incantation", 7, ia_unknown},
        {"unknown", 7, ia_unknown}
    };

static int run(t_server *server, Socket sock, const t_command *commands, size_t size)
{
  char cmd[MESSAGE_MAX_SIZE];
  size_t i;

  i = 0;
  strfromcircular(&server->game.clients[sock].r, cmd);
  while (i < size)
  {
    if (!strncmp(commands[i].cmd, cmd, commands[i].len) &&
        commands[i].exec(server, sock, cmd))
      return (1);
    ++i;
  }
  if (i == size)
    return (commands[size].exec(server, sock, cmd));
  return (0);
}

int  proceed_commands(t_server *server)
{
  int i;

  if (find_command(&server->gui.r) &&
      run(server, server->gui.sock, gui_commands, GUI_END))
    return (1);
  i = 0;
  while (i < server->config.max_player * 2)
  {
    if (find_command(&server->game.clients[i].r) &&
        run(server, server->game.clients[i].sock, ia_commands, IA_END))
      return (1);
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