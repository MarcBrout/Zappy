//
// Created by brout_m on 24/06/17.
//

#ifndef STORE_COMMANDS_H_
# define STORE_COMMANDS_H_
# define MAX_CMD 10
# define CMD_LENGTH 100

# include <stdint.h>

typedef struct s_cmd t_cmd;
typedef struct s_store t_store;

struct s_cmd
{
  char command[CMD_LENGTH];
  uint64_t cooldown;
  struct s_cmd *next;
};

struct s_store
{
  t_cmd *commands;
  uint16_t command_count;
};

/*
** Returns 1 if an allocation error occurred, return 0 otherwise and
** whether the command is added or not. The command is not added if
** the queue is full. Queue size if defined byt the macro MAX_CMD
*/
int store_command(t_store *store, const char *cmd, uint64_t cooldown);

/*
** Returns NULL if no commands were found
*/
char *get_command_from_store(t_store *store);

/*
** Remove the first command, has no effect if the queue is empty
*/
void pop_command(t_store *store);


#endif /* !ZAPPY_STORE_COMMANDS_H_ */
