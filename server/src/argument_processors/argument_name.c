#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arguments/config.h"

int argument_name(t_config *config, int ac, char **argv, int *pos)
{
  int size;

  if (*pos > ac - 3)
    return (1);
  ++*pos;
  if ((config->teams = calloc(10, sizeof(char *))) == NULL)
    return (1);
  config->team_count = 0;
  size = 10;
  while (*pos < ac && argv[*pos][0] != '-')
  {
    if (config->team_count == size - 1)
    {
      if ((config->teams =
               realloc(config->teams, (size + 10) * sizeof(char *))) == NULL)
        return (1);
      size += 10;
    }
    if ((config->teams[config->team_count] = strdup(argv[*pos])) == NULL)
      return (1);
    ++config->team_count;
    ++*pos;
  }
  --*pos;
  return (config->team_count < 2);
}