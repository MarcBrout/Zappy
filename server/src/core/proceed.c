/*
** proceed.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:47:51 2017 brout_m
** Last update Sun Jun 25 02:47:59 2017 brout_m
*/

#include <string.h>
#include "server/gui_commands.h"
#include "server/ia_commands.h"
#include "server/logic_commands.h"
#include "server.h"

static const t_command	gui_commands[GUI_END + 1] =
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
    {NULL, 0, gui_unknown}
  };

static const t_command	ia_commands[IA_END + 1] =
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
    {NULL, 0, ia_unknown}
  };

static const t_command	ia_logic[LOGIC_END + 1] =
 {
  {"Forward", 7, logic_forward},
  {"Right", 5, logic_right},
  {"Left", 4, logic_left},
  {"Look", 4, logic_look},
  {"Inventory", 9, logic_inventory},
  {"Broadcast", 9, logic_broadcast},
  {"Connect_nbr", 11, logic_connect_nbr},
  {"ForkStart", 9, logic_fork_start},
  {"Fork", 4, logic_fork},
  {"Eject", 5, logic_eject},
  {"Take", 4, logic_take},
  {"Set", 3, logic_set},
  {"IncantationStart", 16, logic_incantation_start},
  {"Incantation", 11, logic_incantation},
  {NULL, 0, logic_unknown}
 };

static int		run(t_server *server,
			    t_client *client,
			    const t_command *commands,
			    char *cmd)
{
  size_t		i;

  i = 0;
  log_this("raw command extracted: %s\n", cmd);
  while (commands[i].cmd)
    {
      if (!strncmp(commands[i].cmd, cmd, commands[i].len) &&
	  commands[i].exec(server, client->id, cmd))
	return (1);
      ++i;
    }
  if (!commands[i].cmd)
    return (commands[i].exec(server, client->id, cmd));
  return (0);
}

static int		proceed_commands(t_server *server)
{
  char			cmd[MESSAGE_MAX_SIZE];
  int			i;

  log_this("\t====\nReading GUI commands\n\t====\n");
  while (find_command(&server->gui.r))
    {
      strfromcircular(&server->gui.r, cmd);
      if (run(server, &server->gui, gui_commands, cmd))
	return (1);
    }
  i = 0;
  log_this("\t====\nReading CLIENTS commands\n\t====\n");
  while (i < server->config.max_player * server->config.team_count)
  {
    while (find_command(&server->game.clients[i].r))
      {
	strfromcircular(&server->game.clients[i].r, cmd);
	if (run(server, &server->game.clients[i], ia_commands, cmd))
	  return (1);
      }
    ++i;
  }
  return (0);
}

static int		proceed_logic(t_server *server)
{
  int			i = 0;
  char			*cmd = NULL;

  if (isTick())
    {
      log_this("TICK\n");
      while (i < server->config.max_player * server->config.team_count)
	{
	  if ((cmd = get_command_from_store(&server->game.clients[i].store)))
	    {
	      if (run(server, &server->game.clients[i], ia_logic, cmd))
		return (1);
	      pop_command(&server->game.clients[i].store);
	    }
	  ++i;
	}
    }
  return (0);
}

int			proceed(t_server *server,
				fd_set *fds_read, fd_set *fds_write)
{
  return (proceed_reads(server, fds_read) ||
	  proceed_commands(server) ||
	  proceed_logic(server) ||
	  proceed_writes(server, fds_write));
}
