###############################
##ARGUMENTS/MACRO
MAKEFLAGS += --silent

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
READFLAG = -lreadline -ltermcap
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
				tokenizer/token_operator_incomplete_utils.c \
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
				expansion/expansion2.c \
				expansion/expansion_utils.c \
				expansion/expansion_wildcard.c \
				expansion/expansion_wilcard_psm.c \
				expansion/expansion_wildcard_match.c \
				expansion/expansion_wildcard_utils.c \
				expansion/expansion_wildcard_newargv.c \
				execution/execution.c \
				execution/execute_heredoc.c \
				execution/execute_pipe.c \
				execution/execute_subshell.c \
				execution/execute_redirection.c \
				execution/execute_redirection_utils.c \
				execution/execute_simple_command.c \
				execution/execute_simple_command_utils.c \
				execution/execute_simple_command_builtins.c \
				execution/execute_simple_command_external.c \
				signal/signal.c \
				execution/env.c \
				execution/env_utils.c \
				execution/builtins/cd.c \
				execution/builtins/cd_utils.c \
				execution/builtins/echo.c \
				execution/builtins/env.c \
				execution/builtins/exit.c \
				execution/builtins/export.c \
				execution/builtins/export_utils.c \
				execution/builtins/pwd.c \
				execution/builtins/unset.c \
				execution/builtins/whale.c \
				execution/builtins/shark.c \
				main.c

OBJS = $(FILES:.c=.o)

###############################
##RULES

all: $(NAME)

$(NAME): $(OBJS)

	@make -C libft/
	@echo "\033[1;32m"
	@echo " 🐚 Welcome to																	"
	@echo "▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▖   ▗▖   "
	@echo "▐▛▚▞▜▌  █  ▐▛▚▖▐▌  █  ▐▌   ▐▌ ▐▌▐▌   ▐▌   ▐▌   "
	@echo "▐▌  ▐▌  █  ▐▌ ▝▜▌  █   ▝▀▚▖▐▛▀▜▌▐▛▀▀▘▐▌   ▐▌   "
	@echo "▐▌  ▐▌▗▄█▄▖▐▌  ▐▌▗▄█▄▖▗▄▄▞▘▐▌ ▐▌▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖"
	@echo "                                               "
	@echo " Run with : ./minishell 🪼🐙										"
	@echo "\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READFLAG) -o $(NAME)
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[1;32m" "Cleaning .o \033[0m"
	@rm -f $(OBJS)
	@make -C libft/ clean

fclean: clean
	@echo "\033[1;32m" "Cleaning program \033[0m"
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
