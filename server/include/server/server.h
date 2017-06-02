//
// Created by brout_m on 31/05/17.
//

#ifndef SERVER_DATA_H_
# define SERVER_DATA_H_

# include "arguments/config.h"
# include "server/server_types.h"

typedef struct s_server t_server;
typedef struct s_client t_client;
typedef struct s_ia t_ia;
typedef struct s_egg t_egg;
typedef struct s_inventory t_inventory;
typedef struct s_cell t_cell;
typedef struct s_position t_position;
typedef struct s_game t_game;

struct s_position
{
  int x;
  int y;
};

struct s_cell
{
  Object objects[THYSTAME];
};

struct s_egg
{
  t_egg *next;
  int hatching;
  t_position pos;
};

struct s_ia
{
  Team team;
  Level level;
  Direction dir;
  t_position pos;
  Object inventory[THYSTAME];
};

struct s_client
{
  t_ia ia;
  Socket sock;
  char *message;
};

struct s_game
{
  t_egg *eggs;
  t_cell *map;
  size_t width;
  size_t height;
  t_client *clients;
};

struct s_server
{
  Socket sock;
  t_game game;
  t_config config;
};

#endif /* !SERVER_DATA_H_ */