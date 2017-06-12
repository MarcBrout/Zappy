//
// Created by brout_m on 31/05/17.
//

#ifndef CONFIG_H_
# define CONFIG_H_
# define MAX_WIDTH 255
# define MAX_HEIGHT 255
# define MAX_CLIENT 21

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

typedef struct s_arg t_arg;
typedef struct s_config t_config;
typedef int (*arg_process_t)(t_config *config, int ac, char **argv, int *pos);

struct s_arg
{
  const char *cmd;
  const arg_process_t exec;
  bool ok;
};

struct s_config
{
  uint16_t port;
  uint8_t width;
  uint8_t height;
  char *team1;
  char *team2;
  uint8_t max_player;
  uint16_t time;
};

#endif /* !CONFIG_H_ */
