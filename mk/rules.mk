## Generic rules for Makefiles

$(NAME):	$(OBJ)
		@$(ECHO)
ifeq ($(MODE), CPP)
		@$(ECHO) "$(BLUE) Compiled with : $(BOLD_WHITE)$(CXX)$(CLEAR)"
		@$(ECHO) "$(BLUE) Flags used \t  : $(BOLD_WHITE)$(CXXFLAGS)$(CLEAR)"
else
		@$(ECHO) "$(BLUE) Compiled with : $(BOLD_WHITE)$(CC)$(CLEAR)"
		@$(ECHO) "$(BLUE) Flags used \t  : $(BOLD_WHITE)$(CFLAGS)$(CLEAR)"
endif
		@$(ECHO) "$(BLUE) Dependencies  :$(BOLD_WHITE)$(LDFLAGS)$(CLEAR)"
		@$(ECHO)
		@$(ECHO) "$(BLUE) ==== $(BOLD_WHITE) $(PROJECT_NAME)  Compiled $(BLUE) ==== $(CLEAR)\n\n"
ifeq ($(STATIC), YES)
		@$(LINKER) -o $(NAME) $(OBJ)
else
ifeq ($(MODE), CPP)
	@$(CXX) $(OBJ) -o $(NAME) $(INC) $(LDFLAGS) $(CXXFLAGS)
else
	@$(CC) $(OBJ) -o $(NAME) $(INC) $(LDFLAGS) $(CFLAGS)
endif
endif
		@$(eval PROJECT_NAME=)
		@$(eval LDFLAGS=)
		@$(eval DLL=NO)

all:		$(NAME)

clean:
		@$(ECHO)
		@$(ECHO) "$(BOLD_WHITE) [$(RED)RM$(BOLD_WHITE)] $(PROJECT_NAME) Objects files$(CLEAR)"
		@$(RM) $(OBJ)

fclean:     	clean
		@$(ECHO) "$(BOLD_WHITE) [$(RED)RM$(BOLD_WHITE)] $(PROJECT_NAME) Binary file$(CLEAR)\n"
		@$(RM) $(NAME)

re:		fclean all

.c.o:
		@$(CC) $(CFLAGS) $(INC) $(LDFLAGS) -c $< -o $@ && \
		$(ECHO) "$(BOLD_WHITE) [$(GREEN)OK$(BOLD_WHITE)] Compiled "$<"$(CLEAR)" || \
		$(ECHO) "$(BOLD_WHITE) [$(RED)KO$(BOLD_WHITE)] Compiled "$<"$(CLEAR)"

.cpp.o:
		@$(CXX) $(CXXFLAGS) $(INC) $(LDFLAGS) -c $< -o $@ && \
		$(ECHO) "$(BOLD_WHITE) [$(GREEN)OK$(BOLD_WHITE)] Compiled "$<"$(CLEAR)" || \
		$(ECHO) "$(BOLD_WHITE) [$(RED)KO$(BOLD_WHITE)] Compiled "$<"$(CLEAR)"

.PHONY:		all clean fclean re
