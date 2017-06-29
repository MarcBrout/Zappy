/*
** server_data.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:46:15 2017 brout_m
** Last update Tue Jun 27 16:57:47 2017 brout_m
*/
#ifndef SERVER_DATA_H_
# define SERVER_DATA_H_

# include <stdbool.h>
# include "arguments/config.h"
# include "server_types.h"
# include "circular_tools.h"
# include "store_commands.h"

typedef struct s_server		t_server;
typedef struct s_client		t_client;
typedef struct s_ia		t_ia;
typedef struct s_egg		t_egg;
typedef struct s_inventory	t_inventory;
typedef struct s_cell		t_cell;
typedef struct s_position	t_position;
typedef struct s_game		t_game;
typedef struct s_store		t_store;

# define FIND_POS(x, y, width) ((x) + (y) * (width))

struct				s_position
{
  int				x;
  int				y;
};

struct				s_cell
{
  int				objects[OBJ_COUNT];
};

struct				s_egg
{
  t_egg			*next;
  Team				team;
  ID				id;
  ID				layer;
  int				hatching;
  bool				hatched;
  t_position			pos;
};

struct				s_ia
{
  Team				team;
  Level			level;
  Direction			dir;
  t_position			pos;
  int				inventory[OBJ_COUNT];
  int 				life_unit;
};

struct s_client
{
  ID				id;
  t_ia				ia;
  bool				alive;
  bool				active;
  bool				died;
  Socket			sock;
  t_circular			r;
  t_circular			w;
  t_store			store;
};

struct				s_game
{
  t_egg			*eggs;
  t_cell			*map;
  size_t			width;
  size_t			height;
  uint16_t			max_slot;
  t_client			*clients;
  int				object_tot[OBJ_COUNT];
};

struct				s_server
{
  Socket			ia_sock;
  Socket			gui_sock;
  t_client			gui;
  t_game			game;
  t_config			config;
};

int find_ID(t_server *server, ID client, bool active);
int find_Socket(t_server *server, Socket sock);

#endif /* !SERVER_DATA_H_ */
