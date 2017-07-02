##
## Makefile for GlobalMakefile in /home/pierre/rendu/TEK2/PSU_2016_zappy
##
## Made by PierreBougon
## Login   <pierre@epitech.net>
##
## Started on  Sat Jun 10 20:35:47 2017 PierreBougon
## Last update Sun Jul  2 21:15:35 2017 brout_m
##

include mk/colors.mk mk/commands.mk mk/definitions.mk

SERVER		=	server/

CLIENT_AI	=	ai/


all: zappy_server zappy_ai

zappy_server:
	@$(ECHO) "$(BLUE)/========================\\"
	@$(ECHO) "|         $(BOLD_WHITE)SERVER$(BLUE)         |"
	@$(ECHO) "\========================/ $(WHITE)"
	@$(ECHO)
	@make -s -C $(SERVER) RELEASE=yes

zappy_ai:
	@$(ECHO) "$(BLUE)/========================\\"
	@$(ECHO) "|         $(BOLD_WHITE)  AI  $(BLUE)         |"
	@$(ECHO) "\========================/ $(WHITE)"
	@$(ECHO)
	@make -s -C $(CLIENT_AI) RELEASE=yes

fclean:
	@make -s -C $(SERVER) fclean
	@make -s -C $(CLIENT_AI) fclean

clean:
	@make -s -C $(SERVER) clean
	@make -s -C $(CLIENT_AI) clean

re:	fclean all

.PHONY: clean fclean re zappy_ai zappy_server
