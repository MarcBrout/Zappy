/*
** argument_nbclients.c for zappy in server/src/argument_processors
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 17:05:36 2017 brout_m
** Last update Sat Jun 24 17:06:20 2017 brout_m
*/
#include <stdio.h>
#include <stdlib.h>
#include "arguments/config.h"

int	argument_nbclients(t_config *config, int ac, char **argv, int *pos)
{
  int	nbclients;

  if (*pos > ac - 2)
    return (1);
  ++*pos;
  nbclients = atoi(argv[*pos]);
  if (nbclients < 1 || nbclients >= MAX_CLIENT)
    {
      printf("Max client per team value incorrect, "
	     "value must be between 1 && %d\n", MAX_CLIENT);
      return (1);
    }
  config->max_player = (uint8_t)nbclients;
  return (0);
}
