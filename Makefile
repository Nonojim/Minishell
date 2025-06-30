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
				expansion/expansion_utils.c \
				execution/execution.c \
				execution/execute_heredoc.c \
				execution/execute_pipe.c \
				execution/execute_subshell.c \
				execution/execute_redirection.c \
				execution/execute_simple_command.c \
				execution/execute_simple_command_builtins.c \
				execution/execute_simple_command_external.c \
				signal/signal.c \
				execution/env.c \
				execution/builtins/cd.c \
				execution/builtins/echo.c \
				execution/builtins/env.c \
				execution/builtins/exit.c \
				execution/builtins/export.c \
				execution/builtins/pwd.c \
				execution/builtins/unset.c \
				main.c

OBJS = $(FILES:.c=.o)

###############################
##RULES

all: $(NAME)

$(NAME): $(OBJS)

	@echo "\033[1;32m"
	@echo " 🐚 Welcome to																	"
	@echo "▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▖   ▗▖   "
	@echo "▐▛▚▞▜▌  █  ▐▛▚▖▐▌  █  ▐▌   ▐▌ ▐▌▐▌   ▐▌   ▐▌   "
	@echo "▐▌  ▐▌  █  ▐▌ ▝▜▌  █   ▝▀▚▖▐▛▀▜▌▐▛▀▀▘▐▌   ▐▌   "
	@echo "▐▌  ▐▌▗▄█▄▖▐▌  ▐▌▗▄█▄▖▗▄▄▞▘▐▌ ▐▌▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖"
	@echo "                                               "
	@echo " Run with : ./minishell 🪼🐙										"
	@echo "                                               "
	@make -C libft/
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READFLAG) -o $(NAME)
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[1;32m" "Cleaning .o"
	@rm -f $(OBJS)
	@make -C libft/ clean

fclean: clean
	@echo "\033[1;32m" "Cleaning program"
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
