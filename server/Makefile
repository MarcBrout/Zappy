##
## Makefile for Server Makefile in /home/pierre/rendu/TEK2/PSU_2016_zappy
##
## Made by PierreBougon
## Login   <pierre@e	pitech.net>
##
## Started on  Sat Jun 10 21:33:53 2017 PierreBougon
## Last update Thu Jun 29 10:06:45 2017 brout_m
##


include ../mk/colors.mk ../mk/commands.mk ../mk/definitions.mk

#############################
##### Server variables  #####
#############################

PROJECT_NAME=		zappy_server

NAME=			../$(PROJECT_NAME)

ARGS= 			argument_processors/argument_

GUICMD= 		gui_commands/gui_

GUIEVE=			gui_events/event_

IACMD= 			ia_commands/ia_

IALOG=			ia_logic/logic_

GAMELOG=		game_logic/

CORE= 			core/

MODE=			C

# Project sources

SERVER_RAW_SRC=		server.c 			\
			argument_parsing.c 		\
			help.c 				\
			logger/logger.c 		\
			timer/timer.c 			\
			$(GAMELOG)resources_generator.c	\
			$(GAMELOG)player_manager.c	\
			$(GAMELOG)slot_manager.c	\
			$(GAMELOG)victory_manager.c	\
			$(ARGS)height.c 		\
			$(ARGS)name.c 			\
			$(ARGS)nbclients.c 		\
			$(ARGS)port.c 			\
			$(ARGS)time.c 			\
			$(ARGS)width.c 			\
			$(CORE)circular_buffer.c 	\
			$(CORE)direction_manager.c	\
			$(CORE)eggs.c			\
			$(CORE)internationalization.c 	\
			$(CORE)proceed.c 		\
			$(CORE)proceed_writes.c 	\
			$(CORE)server_launch.c 		\
			$(CORE)socket.c 		\
			$(CORE)accepts.c 		\
			$(CORE)proceed_reads.c 		\
			$(CORE)senders.c 		\
			$(CORE)set_gui.c 		\
			$(CORE)store_commands.c		\
			$(CORE)proceed_player_connection.c \
			$(CORE)free_resources.c \
			$(GUICMD)unknown.c 		\
			$(GUICMD)bct.c 			\
			$(GUICMD)mct.c 			\
			$(GUICMD)msz.c 			\
			$(GUICMD)pin.c 			\
			$(GUICMD)plv.c 			\
			$(GUICMD)ppo.c 			\
			$(GUICMD)sgt.c 			\
			$(GUICMD)sst.c 			\
			$(GUICMD)tna.c 			\
			$(GUICMD)welcome.c 			\
			$(GUICMD)starter.c 			\
			$(GUIEVE)ebo.c 			\
			$(GUIEVE)edi.c 			\
			$(GUIEVE)eht.c 			\
			$(GUIEVE)enw.c 			\
			$(GUIEVE)pbc.c 			\
			$(GUIEVE)pdi.c 			\
			$(GUIEVE)pdr.c 			\
			$(GUIEVE)pex.c 			\
			$(GUIEVE)pfk.c 			\
			$(GUIEVE)pgt.c 			\
			$(GUIEVE)pic.c 			\
			$(GUIEVE)pie.c 			\
			$(GUIEVE)pnw.c 			\
			$(GUIEVE)seg.c 			\
			$(GUIEVE)smg.c 			\
			$(IACMD)broadcast.c		\
			$(IACMD)connect_nbr.c		\
			$(IACMD)death.c			\
			$(IACMD)eject.c			\
		 	$(IACMD)fork.c			\
			$(IACMD)forward.c 		\
			$(IACMD)incantation.c		\
			$(IACMD)inventory.c		\
			$(IACMD)look.c			\
			$(IACMD)left.c 			\
			$(IACMD)right.c 		\
			$(IACMD)take_set.c 		\
			$(IACMD)unknown.c		\
			$(IALOG)broadcast.c		\
			$(IALOG)connect_nbr.c		\
			$(IALOG)eject.c			\
			$(IALOG)fork_start.c		\
		 	$(IALOG)fork.c			\
			$(IALOG)forward.c 		\
			$(IALOG)incantation_start.c	\
			$(IALOG)incantation.c		\
			$(IALOG)inventory.c		\
			$(IALOG)look.c			\
			$(IALOG)left.c 			\
			$(IALOG)right.c 		\
			$(IALOG)take_set.c 		\
			$(IALOG)unknown.c

SERVER_SRC=		$(addprefix src/, $(SERVER_RAW_SRC))

OBJ=			$(SERVER_SRC:.c=.o)

INC=			-Iinclude \
			-Iinclude/logger \
			-Iinclude/timer

LDFLAGS+=		-lm

CFLAGS+=		-Ofast

## Core rules

include ../mk/rules.mk
