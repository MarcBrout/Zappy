/*
** direction_manager.h for zappy in PSU_2016_zappy/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Jun 27 01:33:11 2017 brout_m
** Last update Tue Jun 27 16:56:48 2017 brout_m
*/
#ifndef DIRECTION_MANAGER_H_
# define DIRECTION_MANAGER_H_

# include "server.h"

# define NB_DIRECTIONS 9
# define DIR_PI 3.14159265358979323846
# define DIR_PI_3 DIR_PI / 3.0
# define DIR_PI_6 DIR_PI / 6.0
# define ABS(x) ((x) < 0) ? (x) * -1.0 : (x)

typedef struct	s_direction
{
  int 		x_r;
  int 		y_r;
  int 		id;
}		t_direction;

int		find_direction(t_server *server,
			       t_position *src,
			       t_position *dest,
			       Direction dir_dest);

#endif /* !DIRECTION_MANAGER_H_ */
