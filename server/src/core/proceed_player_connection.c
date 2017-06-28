/*
** proceed_player_connection.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Jun 27 01:43:58 2017 brout_m
** Last update Wed Jun 28 10:37:21 2017 brout_m
*/
#include <string.h>
#include <unistd.h>
#include "server/eggs.h"
#include "server/gui_events.h"

static t_egg *find_egg(t_egg *eggs, ID team)
{
  t_egg *egg = eggs;

  while (egg)
    {
      if (egg->team == team)
	return (egg);
      egg = egg->next;
    }
  return (NULL);
}

static int send_event(t_server *server, t_team *team, ID playerId, t_egg *egg)
{
  log_this("player connected from egg %d\n", egg->id);
  if (event_ebo(server, egg->id) ||
      event_pnw(server, &server->game.clients[playerId]))
    return (1);
  log_this("Removing egg %d\n", egg->id);
  remove_first_egg(server, team->id);
  return (0);
}

static int send_position(t_server *server, ID playerId, t_team *team)
{
  return (send_to_ia(server, playerId, "%d\n",
		     server->config.max_player - team->memberCount) ||
	  send_to_ia(server, playerId, "%d %d\n", server->game.width,
		     server->game.height));
}

static int check_players(t_server *server, t_team *team, ID playerId)
{
  t_egg *egg;

  if (team->memberCount < team->maxCount)
    {
      ++team->memberCount;
      if (team->maxCount > server->config.max_player &&
          team->memberCount > server->config.max_player)
	{
	  if ((egg = find_egg(server->game.eggs, team->id)) && !egg->hatching)
	    {
	      return (send_position(server, playerId, team) ||
		      send_event(server, team, playerId, egg));
	    }
	}
      else
	{
	  return (send_position(server, playerId, team) ||
		  event_pnw(server, &server->game.clients[playerId]));
	}
    }
  if (send_to_ia(server, playerId, "ko\n") ||
      close(server->game.clients[playerId].sock))
    return (1);
  memset(&server->game.clients[playerId], 0, sizeof(t_client));
  return (0);
}

int player_connecting(t_server *server, ID playerId, char *cmd)
{
  t_team *team;
  int     j = 0;

  while (j < server->config.team_count)
    {
      team = &server->config.teams[j];
      if (!strcmp(cmd, team->name))
	{
	  if (check_players(server, team, playerId))
	    return (-1);
	  return (1);
	}
      ++j;
    }
  return (0);
}
