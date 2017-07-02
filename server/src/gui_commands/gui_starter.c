/*
** gui_starter.c for zappy in server/src/gui_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Jun 27 01:34:53 2017 brout_m
** Last update Sun Jul  2 18:12:36 2017 Edouard
*/

#include <stdbool.h>
#include "server/gui_events.h"
#include "server/gui_commands.h"

static bool	gl_guiConnected = false;
static bool	reset = false;

bool	set_gui_connected(bool value, bool set)
{
  if (set)
    {
      gl_guiConnected = value;
      if (value)
	{
	  reset = true;
	}
    }
  return (gl_guiConnected);
}

static int	send_map_cell(t_server *server, uint32_t *cellId)
{
  uint32_t	cell = *cellId;
  uint32_t	height = (uint32_t)server->game.height;
  uint32_t	width = (uint32_t)server->game.width;

  if (cell < width * height)
    {
      if (send_case_content(server, cell % width, cell / width))
	{
	  return (-1);
	}
      ++*cellId;
      return (1);
    }
  return (0);
}

static int	send_player_informations(t_server *server)
{
  ID		id = 0;
  t_client	*newClient;

  while (id < server->game.max_slot)
    {
      newClient = &server->game.clients[id];
      if (newClient->alive)
	{
	  log_this("[PPO] GUI asked for Client '%d' position on:"
		    "\n\tx: %d\n\ty: %d\n\tdir: %d\n ", id,
		   newClient->ia.pos.x,
		   newClient->ia.pos.y,
		   newClient->ia.dir);
	  if (send_to_gui(server, "pnw %d %d %d %d %d %s\n", newClient->id,
			  newClient->ia.pos.x, newClient->ia.pos.y,
			  newClient->ia.dir, newClient->ia.level,
			  server->config.teams[newClient->ia.team]))
	    return (1);
	}
      ++id;
    }
  return (0);
}

static int	send_eggs_informations(t_server *server)
{
  t_egg		*egg;

  egg = server->game.eggs;
  while (egg)
    {
      if (event_enw(server, egg->layer, egg))
	return (1);
      egg = egg->next;
    }
  return (0);
}

int			send_informations(t_server *server)
{
  static uint32_t	cellId = 0;
  int			ret;

  if (reset)
    {
      cellId = 0;
      send_to_gui(server, "msz %d %d\n", server->config.width,
		  server->config.height);
      send_to_gui(server, "sgt %d\n", server->config.time);
      reset = false;
    }
  if ((ret = send_map_cell(server, &cellId)) == 1)
    return (0);
  else if (ret == -1)
    return (1);
  if (gui_tna(server, 0, NULL) || send_player_informations(server) ||
      send_eggs_informations(server))
    return (1);
  set_gui_connected(false, true);
  return (0);
}
