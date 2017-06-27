/*
** direction_manager.h for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:22:52 2017 Edouard
** Last update Tue Jun 27 17:23:02 2017 Edouard
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
  int		x_r;
  int		y_r;
  int		id;
}		t_direction;

int	find_direction(t_server *server,
		       t_position *src,
		       t_position *dest,
		       Direction dir_dest);

#endif /* !DIRECTION_MANAGER_H_ */
