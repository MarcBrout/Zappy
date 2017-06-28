##
## Makefile for AI in /home/pierre/rendu/TEK2/PSU_2016_zappy
##
## Made by PierreBougon
## Login   <pierre@epitech.net>
##
## Started on  Sat Jun 10 21:41:56 2017 PierreBougon
## Last update Mon Jun 26 17:48:59 2017 PierreBougon
##

MODE=	CPP

include ../mk/colors.mk ../mk/commands.mk ../mk/definitions.mk


#############################
#####   AI variables    #####
#############################

PROJECT_NAME=		zappy_ai

NAME=			../$(PROJECT_NAME)


# Project sources

MAIN_SRC=		main.cpp	\
			Core.cpp

TOOLS_SRC=		Logger.cpp	\
			FDManager.cpp	\
			Splitter.cpp    \
			ParseOptions.cpp

EXCEPTIONS_SRC=		ClientError.cpp	\
			SocketError.cpp

NETWORK_SRC=		ASocket.cpp	\
			TCPClient.cpp	\
			Client.cpp	\
			SendCommand.cpp

AILOGIC_SRC=		AILogic.cpp

COREAI_SRC=		CoreAI.cpp

SRC=			$(addprefix src/, $(MAIN_SRC))
SRC+=			$(addprefix src/tools/, $(TOOLS_SRC))
SRC+=			$(addprefix src/exceptions/, $(EXCEPTIONS_SRC))
SRC+=			$(addprefix src/network/, $(NETWORK_SRC))
SRC+=			$(addprefix src/core_ai/, $(COREAI_SRC))
SRC+=			$(addprefix src/ai_logic/, $(AILOGIC_SRC))

OBJ=			$(SRC:.cpp=.o)

INC=			-Iinclude

LDFLAGS+=

CXXFLAGS+=

## Core rules

include ../mk/rules.mk
