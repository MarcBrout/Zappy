/*
** send.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:45:38 2017 brout_m
** Last update Sun Jul  2 15:09:54 2017 Edouard
*/

#ifndef SEND_H_
# define SEND_H_

# include "server_data.h"

int	send_to_gui(t_server *server, char const *fmt, ...);
int	send_to_ia(t_server *server, ID id, char const *fmt, ...);

#endif /* !SEND_H_ */
