/*
** store_commands.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:51:27 2017 brout_m
** Last update Sat Jun 24 16:53:14 2017 brout_m
*/
#ifndef STORE_COMMANDS_H_
# define STORE_COMMANDS_H_
# define MAX_CMD 10
# define CMD_LENGTH 100

# include <stdint.h>
# include <stdbool.h>

typedef struct s_cmd	t_cmd;
typedef struct s_store	t_store;

struct			s_cmd
{
  char			command[CMD_LENGTH];
  uint64_t		cooldown;
  bool			in_limit;
  struct s_cmd		*next;
};

struct			s_store
{
  t_cmd			*commands;
  uint16_t		command_count;
};

/*
** Returns 1 if an allocation error occurred, return 0 otherwise
** whether the command is added or not. The command is not added if
** the queue is full. Queue size is defined by the macro MAX_CMD
** and updated automatically
*/
int store_command(t_store *store, const char *cmd, uint64_t cooldown);

/*
** Returns 1 if an allocation error occurred, return -1 if there are no first
** element in the list (bad use), return 0 otherwise.
*/
int 		store_command_sequel(t_store *store,
				     const char *cmd,
				     uint64_t cooldown);

/*
** Returns NULL if no commands were found
*/
char *get_command_from_store(t_store *store);

/*
** Remove the first command, has no effect if the queue is empty
*/
void pop_command(t_store *store);

#endif /* !STORE_COMMANDS_H_ */
