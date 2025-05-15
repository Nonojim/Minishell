# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/12 11:38:03 by lduflot           #+#    #+#              #
#    Updated: 2025/05/13 14:42:33 by lduflot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


###############################
## ARGUMENTS/MACRO

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
NAME = pipex

###############################
## SOURCES

FILES = pipex.c 
				#file1 
				#file2 


OBJS = $(FILES:.c=.o)

###############################
## RULES


all: intro $(NAME)

$(NAME): $(OBJS)
	@echo "Run pipex"
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

.PHONY: all clean fclean re intro
