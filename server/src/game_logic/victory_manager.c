/*
** victory_manager.c for zappy in /home/login_p/delivery/zappy/victory_manager.c
**
** Made by Prenom Nom
** Login   <prenom.nom@epitech.eu>
**
** Started on  mer. juin 28 21:30:46 2017 Prenom Nom
** Last update mer. juin 28 21:30:46 2017 Prenom Nom
*/

#include "server.h"

Team	check_winner(t_server *server)
{
  Team 	team = 0;
  Level max = 0;
  Team 	max_team = 0;

  while (team < server->config.team_count)
    {
      if (server->config.teams[team].maxlvl - 1 > max)
	{
	  max = server->config.teams[team].maxlvl - 1;
	  max_team = team;
	}
      ++team;
    }
  log_this("Winner is team %d with lvl %d\n", max_team, max);
  return (max_team);
}