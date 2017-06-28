/*
** argument_name.c for zappy in server/src/argument_processors
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 17:04:37 2017 brout_m
** Last update Wed Jun 28 10:32:55 2017 brout_m
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arguments/config.h"

void		set_teams(t_config *config)
{
  int		i = 0;

  while (i < config->team_count)
    {
      config->teams[i].maxCount = config->max_player;
      ++i;
    }
}

static int	is_name_taken(t_config const *config, char const *name)
{
  int		i = 0;

  while (i < config->team_count)
    {
      if (!strcmp(config->teams[i].name, name))
	return (1);
      ++i;
    }
  return (0);
}

static int	resizing(t_config *config, int *size)
{
  if (config->team_count == *size - 1)
    {
      if ((config->teams = realloc(config->teams,
				   (*size + 10) * sizeof(t_team))) == NULL)
	return (1);
      *size += 10;
    }
  return (0);
}

static int	adding_names(t_config *config, int ac, char **argv, int *pos)
{
  int		size = 10;

  if ((config->teams = calloc(10, sizeof(t_team))) == NULL)
    return (1);
  config->team_count = 0;
  while (*pos < ac && argv[*pos][0] != '-')
    {
      if (resizing(config, &size))
	return (0);
      if (is_name_taken(config, argv[*pos]))
	{
	  printf("Team name '%s' already taken.\n", argv[*pos]);
	  return (1);
	}
      if (!(config->teams[config->team_count].name = strdup(argv[*pos])))
	return (1);
      config->teams[config->team_count].id = config->team_count;
      ++config->team_count;
      ++*pos;
    }
  return (0);
}

int		argument_name(t_config *config, int ac, char **argv, int *pos)
{
  if (*pos > ac - 3)
    return (1);
  ++*pos;
  if (adding_names(config, ac, argv, pos))
    return (1);
  if (config->team_count < 2)
    {
      printf("Not enough team names, minimum 2 required.\n");
      return (1);
    }
  --*pos;
  return (0);
}
