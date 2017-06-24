/*
** argument_parsing.c for zappy in server/src
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 17:00:47 2017 brout_m
** Last update Sat Jun 24 17:02:00 2017 brout_m
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arguments/arguments.h"
#include "arguments/config.h"

static t_arg		commands[7] = {
  {"-p", "port", argument_port, false},
  {"-x", "width", argument_width, false},
  {"-y", "height", argument_height, false},
  {"-n", "name", argument_name, false},
  {"-c", "client count", argument_nbclients, false},
  {"-t", "time", argument_time, false},
  {NULL, NULL, NULL, false}
};

void			print_missing_arguments()
{
  t_arg			*it;

  it = commands;
  while (it->exec != NULL)
    {
      if (!it->ok)
	{
	  if (printf("Missing command : %s\n", it->full_cmd) < 0)
	    return ;
	}
      ++it;
    }
}

static int		arguments_validation(char **args)
{
  t_arg			*it;

  it = commands;
  while (it->exec != NULL)
    {
      if (!it->ok)
	{
	  print_missing_arguments();
	  return (print_help(args[0]));
	}
      ++it;
    }
  return (0);
}

int			process_command_line(t_config *config, int ac, char **args)
{
  int			argument;
  t_arg			*it;

  argument = 1;
  while (argument < ac)
    {
      it = commands;
      while (it->exec != NULL)
	{
	  if (!strcmp(it->cmd, args[argument]))
	    {
	      if (it->exec(config, ac, args, &argument))
		return (print_help(args[0]) || EXIT_FAILURE);
	      it->ok = true;
	      break;
	    }
	  ++it;
	}
      if (it->exec == NULL)
	return (print_help(args[0]) || EXIT_FAILURE);
      ++argument;
    }
  return (arguments_validation(args));
}
