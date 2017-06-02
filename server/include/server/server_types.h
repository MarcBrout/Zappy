//
// Created by brout_m on 02/06/17.
//

#ifndef SERVER_TYPES_H_
# define SERVER_TYPES_H_

# include <stddef.h>

typedef int Socket;
typedef int Team;
typedef enum e_object Object;
typedef unsigned int Level;
typedef enum e_direction Direction;
typedef enum e_rdirection RDirection;
typedef enum int ID;

enum e_object
{
  FOOD = 0,
  LINEMATE,
  DERAUMERE,
  SIBUR,
  MENDIANE,
  PHIRAS,
  THYSTAME,
  OBJ_COUNT
};

enum e_direction
{
  NORTH = 1,
  EAST,
  SOUTH,
  WEST
};

enum e_rdirection
{
  SOUTH = 1,
  WEST,
  NORTH,
  EAST
};

const char *nameof(enum e_object obj);

#endif /* !SERVER_TYPES_H_ */
