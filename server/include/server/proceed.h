/*
** proceed.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:44:32 2017 brout_m
** Last update Sun Jul  2 15:08:43 2017 Edouard
*/
#ifndef PROCEED_H_
# define PROCEED_H_

# include <sys/socket.h>
# include "server_data.h"

typedef int (*func_t)(t_server *server, ID id, char *cmd);

enum	GUI_COMMANDS
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
    GRQPHIC,
    GUI_END
  };

enum	IA_COMMANDS
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

enum	IA_LOGICS
{
  LOGIC_FORWARD = 0,
  LOGIC_RIGHT,
  LOGIC_LEFT,
  LOGIC_LOOK,
  LOGIC_INVENTORY,
  LOGIC_BRODCAST,
  LOGIC_CONNECT_NBR,
  LOGIC_FORK_START,
  LOGIC_FORK,
  LOGIC_EJECT,
  LOGIC_TAKE,
  LOGIC_SET,
  LOGIC_INCANTATION_START,
  LOGIC_INCANTATION,
  LOGIC_END
};

typedef struct		s_command
{
  const char		*cmd;
  const size_t		len;
  const func_t		exec;
}			t_command;

int	proceed(t_server *server, fd_set *fds_read, fd_set *fds_write);
int	proceed_writes(t_server *server, fd_set *fds_write);
int	proceed_reads(t_server *server, fd_set *fds_read);
int	proceed_server(t_server *server, fd_set *fds_read);
int	launch_server(t_server *server);
int	set_gui(t_server *server, fd_set *fds_read, fd_set *fds_write);
int	accept_new_client(t_server *server);
int	player_connecting(t_server *server, ID playerId, char *cmd);
int	proceed_one_turn(t_server *server);
void	generate_ressources_start(t_server *server);
void	increment_team_count(t_server *server, Team id);
void	decrement_team_count(t_server *server, Team id);
int	count_empty_slot(t_server *server, Team team);
void	initiate_client_egg(t_server *server,
			    ID id,
			    Team team,
			    t_position *pos);
void	initiate_client(t_server *server, ID id, Team team);
void	set_quit(int sig);
Team	check_winner(t_server *server);
int	write_client(t_server *server, t_client *client, Socket sock);
int	proceed_gui_writes(t_server *server, fd_set *fds_write);
int	read_gui(t_client *gui, Socket sock);
int	proceed_gui_reads(t_server *server, fd_set *fds_read);

#endif /* !PROCEED_H_ */
