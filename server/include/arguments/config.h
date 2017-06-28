/*
** config.h for zappy in server/include/arguments
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:38:06 2017 brout_m
** Last update Sat Jun 24 16:40:17 2017 brout_m
*/
#ifndef CONFIG_H_
# define CONFIG_H_
# define MAX_WIDTH 255
# define MAX_HEIGHT 255
# define MAX_CLIENT 21
# define MAX_TIME 65535

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

typedef int ID;
typedef struct s_team t_team;
typedef struct s_arg		t_arg;
typedef struct s_config	t_config;
typedef int			(*arg_process_t)(t_config *config,
						 int ac,
						 char **argv,
						 int *pos);

struct				s_arg
{
  const char			*cmd;
  const char			*full_cmd;
  const arg_process_t		exec;
  bool				ok;
};

struct s_team
{
  char *name;
  ID id;
  uint32_t memberCount;
  uint32_t maxCount;
  uint32_t maxlvl;
  uint32_t lvlcount;
};

struct s_config
{
  uint16_t			port;
  uint8_t			width;
  uint8_t			height;
  t_team			*teams;
  uint8_t			team_count;
  uint8_t			max_player;
  uint16_t			time;
};

#endif /* !CONFIG_H_ */
