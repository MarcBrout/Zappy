#ifndef ARGUMENTS_H_
# define ARGUMENTS_H_

typedef struct s_config t_config;

int print_help(char *server_name);
int process_command_line(t_config *config, int ac, char **argv);
int argument_port(t_config *config, char **argv, int *pos);
int argument_width(t_config *config, char **argv, int *pos);
int argument_height(t_config *config, char **argv, int *pos);
int argument_name(t_config *config, char **argv, int *pos);
int argument_nbclients(t_config *config, char **argv, int *pos);
int argument_time(t_config *config, char **argv, int *pos);

#endif /* !ZAPPY_ARGUMENTS_H_ */