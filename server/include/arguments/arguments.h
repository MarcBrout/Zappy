/*
** arguments.h for zappy in server/include/arguments
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:37:22 2017 brout_m
** Last update Sat Jun 24 16:37:57 2017 brout_m
*/
#ifndef ARGUMENTS_H_
# define ARGUMENTS_H_

typedef struct s_config t_config;

int print_help(char *server_name);
void set_teams(t_config *config);
int process_command_line(t_config *config, int ac, char **argv);
int argument_port(t_config *config, int ac, char **argv, int *pos);
int argument_width(t_config *config, int ac, char **argv, int *pos);
int argument_height(t_config *config, int ac, char **argv, int *pos);
int argument_name(t_config *config, int ac, char **argv, int *pos);
int argument_nbclients(t_config *config, int ac, char **argv, int *pos);
int argument_time(t_config *config, int ac, char **argv, int *pos);

#endif /* !ARGUMENTS_H_ */
