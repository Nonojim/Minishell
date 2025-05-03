###############################
##ARGUMENTS/MACRO

CC = cc
CFLAGS = -g -lreadline -Wall -Wextra -Werror
NAME = minishell

###############################
##SOURCES

FILES = minishell.c

OBJS = $(FILES:.c=.o)

###############################
##RULES

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compilation of $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning .o"
	@rm -f $(OBJS)
fclean: clean
	@echo "Cleaning program"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
