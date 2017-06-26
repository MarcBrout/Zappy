/*
** eggs.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:36:40 2017 brout_m
** Last update Sun Jun 25 02:38:22 2017 brout_m
*/
#include <server.h>
#include <stdlib.h>
#include "server/gui_events.h"
#include "server/eggs.h"

int		add_egg(t_server *server, t_position *pos, Team id)
{
  t_egg		*egg;
  t_egg		*tmp;

  if ((egg = malloc(sizeof(egg))) == NULL)
    return (1);
  egg->pos.y = pos->y;
  egg->pos.x = pos->x;
  egg->team = id;
  egg->hatching = HATCHING;
  egg->next = NULL;
  tmp = server->game.eggs;
  if (tmp == NULL)
    server->game.eggs = egg;
  else
    {
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = egg;
    }
  return (0);
}

bool		remove_first_egg(t_server *server, Team id)
{
  t_egg		*tmp;
  t_egg		*prev;

  tmp = server->game.eggs;
  prev = NULL;
  while (tmp)
    {
      if (tmp->team == id)
	{
	  if (prev == NULL)
	    server->game.eggs = tmp->next;
	  else
	    prev->next = tmp->next;
	  free(tmp);
	  return (true);
	}
      prev = tmp;
      tmp = tmp->next;
    }
  return (false);
}

void		free_eggs(t_server *server)
{
  t_egg		*tmp;
  t_egg		*prev;

  tmp = server->game.eggs;
  while (tmp)
    {
      prev = tmp;
      tmp = tmp->next;
      free(prev);
    }
}

void		check_eggs(t_server *server)
{
  t_egg		*tmp;
  t_egg		*prev;

  tmp = server->game.eggs;
  prev = NULL;
  while (tmp)
    {
      --tmp->hatching;
      if (tmp->hatching == 0)
	{
	  if (prev == NULL)
	    server->game.eggs = tmp->next;
	  else
	    prev->next = tmp->next;
	  tmp = tmp->next;
          event_edi(server, tmp->id);
	  free(tmp);
	}
      else
	{
	  prev = tmp;
	  tmp = tmp->next;
	}
    }
}
