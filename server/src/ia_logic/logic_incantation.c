/*
** logic_incantation.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:30:41 2017 Edouard
** Last update Wed Jun 28 10:46:01 2017 brout_m
*/

#include "server/gui_commands.h"
#include "server/logic_commands.h"
#include "server/gui_events.h"
#include "server/ia_commands.h"

static const int incant_tab[MAX_INCANT][OBJ_COUNT] =
 {
  {1, 1, 0, 0, 0, 0, 0},
  {2, 1, 1, 1, 0, 0, 0},
  {2, 2, 0, 1, 0, 2, 0},
  {4, 1, 1, 2, 0, 1, 0},
  {4, 1, 2, 1, 3, 0, 0},
  {6, 1, 2, 3, 0, 1, 0},
  {6, 2, 2, 2, 2, 2, 1}
 };

static void	count_team_lvl(t_server *server, t_team *team)
{
  ID 		cli = 0;

  team->lvlcount = 0;
  while (cli < server->game.max_slot)
    {
      if (server->game.clients[cli].ia.team == team->id &&
	  server->game.clients[cli].ia.level >= team->maxlvl)
	++team->lvlcount;
      ++cli;
    }
}

static void	incr_lvl_team(t_server *server, Team id, Level lvl)
{
  t_team	*team;

  team = &server->config.teams[id];
  if (team->maxlvl == lvl)
    {
      ++team->lvlcount;
      if (team->lvlcount == 6)
	{
	  if (team->maxlvl == LEVEL_END)
	    {
	      set_quit(0);
	      return ;
	    }
	  ++team->maxlvl;
	  count_team_lvl(server, team);
	}
    }
}

static int	send_incantation_end(t_server *server,
				     t_client *client,
				     int max_player)
{
  ID 		cli = 0;
  int 		nb_player = 0;

  while (nb_player < max_player && cli < server->game.max_slot)
    {
      if (server->game.clients[cli].alive &&
	  server->game.clients[cli].ia.pos.x == client->ia.pos.x &&
	  server->game.clients[cli].ia.pos.y == client->ia.pos.y)
	{
	  ++server->game.clients[cli].ia.level;
	  incr_lvl_team(server, client->ia.team, client->ia.level);
	  send_player_lvl(server, cli);
	  send_to_ia(server, cli, "Current level: %u\n",
		     server->game.clients[cli].ia.level);
	  ++nb_player;
	}
      ++cli;
    }
  return (0);
}

int		logic_incantation(t_server *server, ID id, char *cmd)
{
  t_client	*client;
  t_cell	*cell;
  Object	obj;

  (void)cmd;
  client = &server->game.clients[id];
  cell = &server->game.map[FIND_POS(client->ia.pos.x,
				    client->ia.pos.y,
				    server->config.width)];
  server->game.clients[id].ia.incanting = false;
  if (check_incantation(server, id, client, cell) == 1)
    {
      event_pie(server, &client->ia.pos, 0);
      return (0);
    }
  event_pie(server, &client->ia.pos, 1);
  obj = LINEMATE;
  while (obj < OBJ_COUNT)
    {
      cell->objects[obj] -= incant_tab[client->ia.level][obj];
      server->game.object_tot[obj] -= incant_tab[client->ia.level][obj];
      ++obj;
    }
  send_case_content(server, client->ia.pos.x, client->ia.pos.y);
  return (send_incantation_end(server, client,
			       incant_tab[client->ia.level][0]));
}
