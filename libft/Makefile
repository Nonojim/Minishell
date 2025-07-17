#sources files
SRC = ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_swap.c ft_memset.c ft_bzero.c ft_memcpy.c \
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c \
ft_memchr.c ft_memcmp.c ft_atoi.c ft_calloc.c ft_sort_int_tab.c ft_strdup.c ft_substr.c ft_strtrim.c ft_strmapi.c ft_striteri.c \
ft_strjoin.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c \
get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
ft_fprintf/ft_fprintf.c \
ft_fprintf/ft_printadress.c \
ft_fprintf/ft_printhexamaj.c \
ft_fprintf/ft_printhexaminus.c \
ft_fprintf/ft_printnbr.c \
ft_fprintf/ft_printchar.c \
ft_fprintf/ft_printstr.c \
ft_fprintf/ft_printnbrunsigned.c
#append .o to each .c files in the SRC
#OBJS := $(SRC:%.c=%.o)
OBJS = ${SRC:.c=.o}
#build target name
NAME = libft.a
#compiler
CC = cc
#compiler flags
CCFLAGS = -Wall -Wextra -Werror
#include directory == dossier includes
INC_DIR = .
#preprocessor flag
CPPFLAGS = -I $(INC_DIR)
#rm
RM = rm -f
#archive
ARNAME = ar rcs $(NAME)
#first rull is always "all" she is calling $(NAME)
all: $(NAME)
#NAME  "@"hide in command in terminal
$(NAME): $(OBJS)
	@$(ARNAME) $(OBJS)
# "%.o" rule compie .c file into corresponding .o file
# "%" is a wildcard for "name of the files without extension"
# $@ = target, here target = .o "$<" = first dependencies here = .c
%.o: %.c
	@$(CC) $(CPPFLAGS) $(CCFLAGS) -o $@ -c $<
#clean delete all .o files
clean:
	@$(RM) $(OBJS)
#after executing clean delete the lib
fclean: clean
	@$(RM) $(NAME)
#delete everything then re create it
re: fclean all
#phony targets
.PHONY: all clean fclean re
