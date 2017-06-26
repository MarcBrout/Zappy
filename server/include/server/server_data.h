//
// Created by brout_m on 31/05/17.
//

#ifndef SERVER_DATA_H_
# define SERVER_DATA_H_

# include <stdbool.h>
# include "arguments/config.h"
# include "server_types.h"
# include "circular_tools.h"

typedef struct s_server t_server;
typedef struct s_client t_client;
typedef struct s_ia t_ia;
typedef struct s_egg t_egg;
typedef struct s_inventory t_inventory;
typedef struct s_cell t_cell;
typedef struct s_position t_position;
typedef struct s_game t_game;

#define FIND_POS(x, y, width) ((x) + (y) * (width))

struct s_position
{
  int x;
  int y;
};

struct s_cell
{
  int objects[OBJ_COUNT];
};

struct s_egg
{
  t_egg *next;
  Team team;
  int hatching;
  t_position pos;
};

struct s_ia
{
  Team team;
  Level level;
  Direction dir;
  t_position pos;
  int inventory[OBJ_COUNT];
};

struct s_client
{
  ID id;
  t_ia ia;
  bool alive;
  Socket sock;
  t_circular r;
  t_circular w;
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
  Socket ia_sock;
  Socket gui_sock;
  t_client gui;
  t_game game;
  t_config config;
};

int find_ID(t_server *server, ID client, bool active);
int find_Socket(t_server *server, Socket sock);

#endif /* !SERVER_DATA_H_ */