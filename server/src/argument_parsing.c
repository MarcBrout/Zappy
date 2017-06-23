#include <stdlib.h>
#include <string.h>
#include "arguments/arguments.h"
#include "arguments/config.h"

static t_arg commands[7] = {{"-p", argument_port, false},
                            {"-x", argument_width, false},
                            {"-y", argument_height, false},
                            {"-n", argument_name, false},
                            {"-c", argument_nbclients, false},
                            {"-t", argument_time, false},
                            {NULL, NULL, false}};

static int arguments_validation(char **args)
{
  t_arg *it;

  it = commands;
  while (it->exec != NULL)
    {
      if (!it->ok)
	return (print_help(args[0]));
      ++it;
    }
  return (0);
}

int process_command_line(t_config *config, int ac, char **args)
{
  int    argument;
  t_arg *it;

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