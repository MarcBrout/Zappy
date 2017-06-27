/*
** direction_manager.c for zappy in /Documents/reseau/PSU_2016_zappy
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:21:11 2017 Edouard
** Last update Tue Jun 27 17:21:27 2017 Edouard
*/

#include <math.h>
#include <stdlib.h>
#include "server.h"
#include "server/direction_manager.h"

static const t_direction direction_tab[NB_DIRECTIONS] =
 {
  {0, 0, 0},
  {1, 0, 1},
  {1, -1, 2},
  {0, -1, 3},
  {-1, -1, 4},
  {-1, 0, 5},
  {-1, 1, 6},
  {0, 1, 7},
  {1, 1, 8}
 };

static size_t	calc_len(int src, int dest, size_t width, bool direct)
{
  size_t 	len;

  if (direct == true)
    {
      len = src >= dest ? src - dest : dest - src;
      return (len);
    }
  else
    {
      len = dest < src ? dest + width - src : src + width - dest;
    }
  return (len);
}

static int	find_value_prev_y(int len_x, int len_y)
{
  double 	val;

  if (len_x == 0)
    return (1);
  val = atan((double) len_y / (double) len_x);
  if (ABS(val) > DIR_PI_6)
    return (1);
  return (0);
}

static int	find_value_prev_x(size_t len_x, size_t len_y)
{
  double 	val;

  if (len_x == 0)
    return (0);
  val = atan((double) len_y / (double) len_x);
  if (ABS(val) > DIR_PI_3)
    return (0);
  return (1);
}

static void	change_dir(Direction dir, int *pos_x, int *pos_y)
{
  int 		tmp;

  if (dir == WEST)
    {
      *pos_x = *pos_x * -1;
      *pos_y = *pos_y * -1;
    }
  else if (dir != EAST)
    {
      tmp = *pos_x;
      *pos_x = dir == NORTH ? *pos_y : *pos_y * -1;
      *pos_y = dir == NORTH ? tmp * -1 : tmp;
    }
}

int		find_direction(t_server *server,
			       t_position *src,
			       t_position *dest,
			       Direction dir_dest)
{
  size_t 	len_x;
  size_t 	len_y;
  size_t	tmp;
  int 		x_prev;
  int 		y_prev;
  int 		i;

  tmp = calc_len(src->x, dest->x, server->config.width, true);
  len_x = calc_len(src->x, dest->x, server->config.width, false);
  x_prev = (len_x < tmp ? -1 : 1) * (src->x < dest->x ? -1 : 1);
  len_x = len_x < tmp ? len_x : tmp;
  tmp = calc_len(src->y, dest->y, server->config.height, true);
  len_y = calc_len(src->y, dest->y, server->config.height, false);
  y_prev = (len_y < tmp ? -1 : 1) *  (src->y < dest->y ? -1 : 1);
  len_y = len_y < tmp ? len_y : tmp;
  x_prev = x_prev * find_value_prev_x(len_x, len_y);
  y_prev = y_prev * find_value_prev_y(len_x, len_y);
  change_dir(dir_dest, &x_prev, &y_prev);
  i = -1;
  while (++i < NB_DIRECTIONS)
    {
      if (direction_tab[i].x_r == x_prev && direction_tab[i].y_r == y_prev)
	return (direction_tab[i].id);
    }
  return (0);
}
