/*
** argument_height.c for zappy in server/src/argument_processors
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 17:03:49 2017 brout_m
** Last update Sun Jul  2 15:32:45 2017 Edouard
*/

#include <stdio.h>
#include <stdlib.h>
#include "arguments/config.h"

int	argument_height(t_config *config, int ac, char **argv, int *pos)
{
  int	height;

  if (*pos > ac - 2)
    return (1);
  ++*pos;
  height = atoi(argv[*pos]);
  if (height < 2 || height >= MAX_HEIGHT)
    {
      printf("Height value incorrect, value must be between 2 && %d\n",
	     MAX_HEIGHT);
      return (1);
    }
  config->height = (uint8_t)height;
  return (0);
}
