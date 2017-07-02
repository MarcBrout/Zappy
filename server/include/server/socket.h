/*
** socket.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:50:25 2017 brout_m
** Last update Sun Jul  2 15:18:17 2017 Edouard
*/

#ifndef SOCKET_H_
# define SOCKET_H_

# include <stdint.h>
# include "server_types.h"

int	create_socket(Socket *s, uint16_t port, int q);

#endif /* !SOCKET_H_ */
