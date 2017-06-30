/*
** eggs.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:41:47 2017 brout_m
** Last update Fri Jun 30 15:04:37 2017 duhieu_b
*/

#ifndef EGGS_H_
# define EGGS_H_

# define HATCHING 600

#include "server.h"

t_egg	*add_egg(t_server *server, t_position *pos, Team id);
bool	remove_first_egg(t_server *server, Team id);
void	free_eggs(t_server *server);
void	check_eggs(t_server *server);
void free_resources(t_server *server);

#endif /* !EGGS_H_ */
