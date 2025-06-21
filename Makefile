###############################
##ARGUMENTS/MACRO
MAKEFLAGS += --silent

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
READFLAG = -lreadline
NAME = minishell
LIBFT = libft/libft.a

###############################
##SOURCES

FILES = tokenizer/tokenizer.c \
				tokenizer/token_operator.c \
				tokenizer/token_bracket.c \
				tokenizer/token_quote.c \
				tokenizer/token_utils.c \
				tokenizer/token_word.c \
				tokenizer/token_type.c \
				tokenizer/token_heredoc.c \
				tokenizer/token_heredoc_utils.c \
				tokenizer/token_operator_incomplete.c \
				parser/ast_utils.c \
				parser/ast_utils_bool.c \
				parser/line.c \
				parser/logical_and.c \
				parser/logical_or.c \
				parser/pipeline.c \
				parser/command.c \
				parser/error.c \
				parser/simple_command.c \
				parser/redirection.c \
				parser/word.c \
				parser/print_ast.c \
				expansion/expansion.c \
				execution/resolver.c \
				main.c

OBJS = $(FILES:.c=.o)

###############################
##RULES

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compilation of $(NAME)"
	@make -C libft/
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READFLAG) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning .o"
	@rm -f $(OBJS)
	@make -C libft/ clean

fclean: clean
	@echo "Cleaning program"
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
