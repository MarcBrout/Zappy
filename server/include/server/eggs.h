//
// Created by puilla_e on 09/06/17.
//

#ifndef EGGS_H_
# define EGGS_H_

# define HATCHING 600

#include "server.h"

int	add_egg(t_server *server, t_position *pos, Team id);
bool	remove_first_egg(t_server *server, Team id);
void	free_eggs(t_server *server);
void	check_eggs(t_server *server);

#endif /* !EGGS_H_ */