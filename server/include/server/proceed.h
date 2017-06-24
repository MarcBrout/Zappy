/*
** proceed.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:44:32 2017 brout_m
** Last update Sat Jun 24 16:45:32 2017 brout_m
*/
#ifndef PROCEED_H_
# define PROCEED_H_

# include <sys/socket.h>
# include "server/server_data.h"

typedef int		(*func_t)(t_server *server, ID id, char *cmd);

enum			GUI_COMMANDS
  {
    MSZ = 0,
    BCT,
    MCT,
    TNA,
    PPO,
    PLV,
    PIN,
    SGT,
    SST,
    GUI_END
  };

enum			IA_COMMANDS
  {
    FORWARD = 0,
    RIGHT,
    LEFT,
    LOOK,
    INVENTORY,
    BRODCAST,
    CONNECT_NBR,
    FORK,
    EJECT,
    TAKE,
    SET,
    INCANTATION,
    IA_END
  };

typedef struct		s_command
{
  const char		*cmd;
  const size_t		len;
  const func_t		exec;
}			t_command;

int proceed(t_server *server, fd_set *fds_read, fd_set *fds_write);
int proceed_writes(t_server *server, fd_set *fds_write);
int proceed_reads(t_server *server, fd_set *fds_read);
int launch_server(t_server *server);
int set_gui(t_server *server, fd_set *fds_read, fd_set *fds_write);
int accept_new_gui(t_server *server);
int accept_new_client(t_server *server);

#endif /* !PROCEED_H_ */
