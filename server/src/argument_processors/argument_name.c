#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arguments/config.h"

static int is_name_taken(t_config const *config, char const *name)
{
  int i = 0;

  while (i < config->team_count)
  {
    if (!strcmp(config->teams[i], name))
      return (1);
    ++i;
  }
  return (0);
}

int adding_names(t_config *config, int ac, char **argv, int *pos)
{
  int size = 10;

  if ((config->teams = calloc(10, sizeof(char *))) == NULL)
    return (1);
  config->team_count = 0;
  while (*pos < ac && argv[*pos][0] != '-')
    {
      if (config->team_count == size - 1)
	{
	  if ((config->teams = realloc(config->teams,
	                               (size + 10) * sizeof(char *))) == NULL)
	    return (1);
	  size += 10;
	}
      if (is_name_taken(config, argv[*pos]))
      {
        printf("Team name '%s' already taken.\n", argv[*pos]);
        return (1);
      }
      if ((config->teams[config->team_count] = strdup(argv[*pos])) == NULL)
	return (1);
      ++config->team_count;
      ++*pos;
    }
  return (0);
}

int argument_name(t_config *config, int ac, char **argv, int *pos)
{
  if (*pos > ac - 3)
    return (1);
  ++*pos;
  if(adding_names(config, ac, argv, pos))
    return (1);
  if (config->team_count < 2)
  {
    printf("Not enough team names, minimum 2 required.\n");
    return (1);
  }
  --*pos;
  return (0);
}