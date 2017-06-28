/*
** player_manager.c for zappy in /home/login_p/delivery/zappy/player_manager.c
**
** Made by Prenom Nom
** Login   <prenom.nom@epitech.eu>
**
** Started on  mer. juin 28 20:49:55 2017 Prenom Nom
** Last update mer. juin 28 20:49:55 2017 Prenom Nom
*/

#include <server.h>
#include <stdlib.h>

void	initiate_client(t_server *server, ID id, Team team)
{
  server->game.clients[id].alive = true;
  server->game.clients[id].ia.level = 1;
  server->game.clients[id].ia.team = team;
  server->game.clients[id].ia.pos.x = rand() % server->config.width;
  server->game.clients[id].ia.pos.y = rand() % server->config.height;
  server->game.clients[id].ia.dir = rand() % 4 + 1;
  server->game.clients[id].ia.inventory[FOOD] = FOOD_START;
}

void	initiate_client_egg(t_server *server,
			    ID id,
			    Team team,
			    t_position *pos)
{
  server->game.clients[id].alive = true;
  server->game.clients[id].ia.level = 1;
  server->game.clients[id].ia.team = team;
  server->game.clients[id].ia.pos.x = pos->x;
  server->game.clients[id].ia.pos.y = pos->y;
  server->game.clients[id].ia.dir = rand() % 4 + 1;
  server->game.clients[id].ia.inventory[FOOD] = FOOD_START;
}