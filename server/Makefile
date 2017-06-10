##
## Makefile for Server Makefile in /home/pierre/rendu/TEK2/PSU_2016_zappy
## 
## Made by PierreBougon
## Login   <pierre@epitech.net>
## 
## Started on  Sat Jun 10 21:33:53 2017 PierreBougon
## Last update Sat Jun 10 22:02:01 2017 PierreBougon
##

include ../mk/colors.mk ../mk/commands.mk ../mk/definitions.mk


#############################
##### Server variables  #####
#############################

PROJECT_NAME=		zappy_server

NAME=			../$(PROJECT_NAME)

ARGS= 			argument_processors/argument_

# Project sources

SERVER_RAW_SRC=		server.c \
			argument_parsing.c \
			help.c \
			$(ARGS)height.c \
			$(ARGS)name.c \
			$(ARGS)nbclients.c \
			$(ARGS)port.c \
			$(ARGS)time.c \
			$(ARGS)width.c

SERVER_SRC=		$(addprefix src/, $(SERVER_RAW_SRC))

OBJ=			$(SERVER_SRC:.c=.o)

INC=			-Iinclude

LDFLAGS+=

CFLAGS+=		-Ofast

## Core rules

include ../mk/rules.mk
