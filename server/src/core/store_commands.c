/*
** store_commands.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:54:50 2017 brout_m
** Last update Sun Jun 25 02:54:57 2017 brout_m
*/
#include <string.h>
#include <stdlib.h>
#include "server/store_commands.h"

static int		add_command(t_cmd **first,
				    const char *cmd,
				    uint64_t cooldown)
{
  t_cmd		*node;
  t_cmd		*cur;

  if ((node = calloc(1, sizeof(*node))) == NULL)
    return (1);
  node->cooldown = cooldown;
  strncpy(node->command, cmd, CMD_LENGTH);
  cur = *first;
  if (!cur)
    {
      *first = node;
      return (0);
    }
  while (cur->next != NULL)
    cur = cur->next;
  cur->next = node;
  return (0);
}

int			store_command(t_store *store,
				      const char *cmd,
				      uint64_t cooldown)
{
  if (store->command_count >= MAX_CMD)
    return (0);
  if (add_command(&store->commands, cmd, cooldown))
    return (1);
  ++store->command_count;
  return (0);
}

char			*get_command_from_store(t_store *store)
{
  t_cmd		*first;

  if (store->command_count)
    {
      first = store->commands;
      if (first->cooldown == 0)
	{
	  return (first->command);
	}
      else
	{
	  --first->cooldown;
	}
    }
  return (NULL);
}

void			pop_command(t_store *store)
{
  t_cmd		*first;

  if (store->command_count)
    {
      first = store->commands;
      store->commands = first->next;
      free(first);
      --store->command_count;
    }
}
