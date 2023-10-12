NAME = libft.a
EXEC = prog
ORIGIN = main.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_strlen.c ft_tolower.c ft_toupper.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_isascii.c ft_strchr.c ft_strnstr.c ft_atoi.c ft_strrchr.c ft_memset.c ft_bzero.c  ft_memcpy.c  ft_calloc.c ft_strdup.c ft_substr.c ft_strlcpy.c ft_strlcat.c ft_strncmp.c ft_striteri.c ft_memcmp.c ft_memchr.c ft_memmove.c ft_strmapi.c ft_strjoin.c ft_itoa.c ft_strtrim.c ft_split.c ft_putnbr.c ft_putstr.c ft_putchar.c ft_strncpy.c ft_printf.c ft_printf_utils.c ft_libft_utils.c ft_itoa_variant.c ft_free_str.c

# nommage automatique des fichiers objets .o en fonction des noms de source .c
OBJ = $(SRC:.c=.o)

all: $(NAME)

#generer le fichier principale de l alib (.a)
$(NAME):
	@$(CC) $(CFLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJ)

#compiler la lib (pour tester ou autre), necessite un main
compil:
	@$(CC) $(CFLAGS) $(ORIGIN) $(SRC) -o $(EXEC)
	@./$(EXEC)

#supprimer les fichier .o
clean:
	@rm -rf *.o

#supprimer les fichier .a, .o et l'executable
fclean : clean
	@rm -rf $(NAME) $(EXEC)
	@echo "$(COLOUR_BLUE)$(NAME) fclean 🐳$(END_COLOR)"

re: fclean all

#securisation du Makefile : indique au compilateurs les regles contenue dans le fichier
.PHONY: all clean fclean re
