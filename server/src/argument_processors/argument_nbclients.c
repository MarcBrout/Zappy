#include <stdlib.h>
#include "arguments/config.h"

int argument_nbclients(t_config *config, int ac, char **argv, int *pos)
{
  int nbclients;

  if (*pos > ac - 2)
    return (1);
  ++*pos;
  nbclients = atoi(argv[*pos]);
  if (nbclients < 2 || nbclients >= MAX_CLIENT)
    return (1);
  config->max_player = (uint8_t)nbclients;
  return (0);
}