##
## Makefile for Server Makefile in /home/pierre/rendu/TEK2/PSU_2016_zappy
##
## Made by PierreBougon
## Login   <pierre@e	pitech.net>
##
## Started on  Sat Jun 10 21:33:53 2017 PierreBougon
## Last update Fri Jun 23 17:34:42 2017 brout_m
##

include ../mk/colors.mk ../mk/commands.mk ../mk/definitions.mk

#############################
##### Server variables  #####
#############################

PROJECT_NAME=		zappy_server

NAME=				../$(PROJECT_NAME)

ARGS= 				argument_processors/argument_

GUICMD= 			gui_commands/gui_

GUIEVE=				gui_events/event_

IACMD= 				ia_commands/ia_

CORE= 				core/

# Project sources

SERVER_RAW_SRC=		server.c 						\
					argument_parsing.c 				\
					help.c 							\
					logger/logger.c 				\
					timer/timer.c 					\
					$(ARGS)height.c 				\
					$(ARGS)name.c 					\
					$(ARGS)nbclients.c 				\
					$(ARGS)port.c 					\
					$(ARGS)time.c 					\
					$(ARGS)width.c 					\
					$(CORE)circular_buffer.c 		\
					$(CORE)internationalization.c 	\
					$(CORE)proceed.c 				\
					$(CORE)proceed_writes.c 		\
					$(CORE)server_launch.c 			\
					$(CORE)socket.c 				\
					$(CORE)accepts.c 				\
					$(CORE)proceed_reads.c 			\
					$(CORE)senders.c 				\
					$(CORE)set_gui.c 				\
					$(GUICMD)unknown.c 				\
					$(GUICMD)bct.c 					\
					$(GUICMD)mct.c 					\
					$(GUICMD)msz.c 					\
					$(GUICMD)pin.c 					\
					$(GUICMD)plv.c 					\
					$(GUICMD)ppo.c 					\
					$(GUICMD)sgt.c 					\
					$(GUICMD)sst.c 					\
					$(GUICMD)tna.c 					\
					$(GUIEVE)ebo.c 					\
					$(GUIEVE)edi.c 					\
					$(GUIEVE)eht.c 					\
					$(GUIEVE)enw.c 					\
					$(GUIEVE)pbc.c 					\
					$(GUIEVE)pdi.c 					\
					$(GUIEVE)pdr.c 					\
					$(GUIEVE)pex.c 					\
					$(GUIEVE)pfk.c 					\
					$(GUIEVE)pgt.c 					\
					$(GUIEVE)pic.c 					\
					$(GUIEVE)pie.c 					\
					$(GUIEVE)pnw.c 					\
					$(GUIEVE)seg.c 					\
					$(GUIEVE)smg.c 					\
					$(IACMD)unknown.c

SERVER_SRC=			$(addprefix src/, $(SERVER_RAW_SRC))

OBJ=				$(SERVER_SRC:.c=.o)

INC=				-Iinclude \
					-Iinclude/logger \
					-Iinclude/timer

LDFLAGS+=

CFLAGS+=			-Ofast

## Core rules

include ../mk/rules.mk

