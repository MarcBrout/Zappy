##
## Makefile for GlobalMakefile in /home/pierre/rendu/TEK2/PSU_2016_zappy
## 
## Made by PierreBougon
## Login   <pierre@epitech.net>
## 
## Started on  Sat Jun 10 20:35:47 2017 PierreBougon
## Last update Sat Jun 10 22:31:59 2017 PierreBougon
##

include mk/colors.mk mk/commands.mk mk/definitions.mk

SERVER		=	server/

CLIENT_AI	=	ai/

CLIENT_UI	=	gui/


all: server ai gui

server:
	@$(ECHO) "$(BLUE)/========================\\"
	@$(ECHO) "|         $(BOLD_WHITE)SERVER$(BLUE)         |"
	@$(ECHO) "\========================/ $(WHITE)"
	@$(ECHO)
	@make -s -C $(SERVER) RELEASE=YES

ai:
	@$(ECHO) "$(BLUE)/========================\\"
	@$(ECHO) "|         $(BOLD_WHITE)  AI  $(BLUE)         |"
	@$(ECHO) "\========================/ $(WHITE)"
	@$(ECHO)
	@make -s -C $(CLIENT_AI) RELEASE=YES

gui:
	@$(ECHO) "$(BLUE)/========================\\"
	@$(ECHO) "|         $(BOLD_WHITE)  UI  $(BLUE)         |"
	@$(ECHO) "\========================/ $(WHITE)"
	@$(ECHO)
	@make -s -C $(CLIENT_UI) RELEASE=YES

fclean:
	@make -s -C $(SERVER) fclean
	@make -s -C $(CLIENT_AI) fclean
	@make -s -C $(CLIENT_UI) fclean

clean:
	@make -s -C $(SERVER) clean
	@make -s -C $(CLIENT_AI) clean
	@make -s -C $(CLIENT_UI) clean

re:	fclean all

.PHONY: clean fclean re ai gui server



############################################

#### Dependencies part

# dependencies:
# 	@$(ECHO) "$(BLUE)/=================================\\"
# 	@$(ECHO) "=======### $(BOLD_WHITE)DEPENDENCIES$(BLUE) ###========"
# 	@$(ECHO) "\=================================/ $(WHITE)"
# 	@$(ECHO)
# 	@make -s -C $(SOUND) STATIC=YES
