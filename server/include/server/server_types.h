/*
** server_types.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:49:08 2017 brout_m
** Last update Tue Jun 27 16:58:41 2017 brout_m
*/
#ifndef SERVER_TYPES_H_
# define SERVER_TYPES_H_

# include <stddef.h>

typedef int			Socket;
typedef int			Team;
typedef enum e_object		Object;
typedef unsigned int		Level;
typedef enum e_direction	Direction;
typedef enum e_rdirection	RDirection;
typedef int			ID;
typedef struct s_luck t_luck;

enum				e_object
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

struct				s_luck
{
  const enum e_object		type;
  double			value;
};

enum				e_direction
  {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
  };

enum				e_rdirection
  {
    RSOUTH = 1,
    RWEST,
    RNORTH,
    REAST
  };

const char *nameof(enum e_object obj);

#endif /* !SERVER_TYPES_H_ */
