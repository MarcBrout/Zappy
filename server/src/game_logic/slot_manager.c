/*
** slot_manager.c for zappy in zappy/server
**
** Made by Edouard Puillandre
** Login   <edouard.puillandre@epitech.eu>
**
** Started on  mer. juin 28 17:16:11 2017 Edouard
** Last update mer. juin 28 17:16:11 2017 Edouard
*/

#include "server.h"

static size_t 	count_eggs(t_server *server, Team team)
{
  t_egg		*egg;
  size_t 	nb_eggs;

  egg = server->game.eggs;
  nb_eggs = 0;
  while (egg != NULL)
    {
      if (egg->team == team && egg->hatched)
	++nb_eggs;
      egg = egg->next;
    }
  return (nb_eggs);
}

int		count_empty_slot(t_server *server, Team id)
{
  t_team	*team;

  team = &server->config.teams[id];
  return (team->maxCount - team->memberCount);
}

void		increment_team_count(t_server *server, Team id)
{
  t_team	*team;
  size_t 	nb_egg;

  nb_egg = count_eggs(server, id);
  team = &server->config.teams[id];
  if (team->memberCount >= server->config.max_player ||
      (server->config.max_player - team->memberCount) < nb_egg)
    ++team->maxCount;
}

void		decrement_team_count(t_server *server, Team id)
{
  t_team	*team;

  team = &server->config.teams[id];
  if (team->maxCount > server->config.max_player)
    --team->maxCount;
}