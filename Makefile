NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

SRC =  builtin/builtins.c builtin/cd.c minishell.c outils/spl.c outils/list.c  builtin/echo.c builtin/env.c \
	  builtin/export.c builtin/pwd.c builtin/unset.c outils/ft_atoi.c outils/ft_itoa.c builtin/exit.c outils/ft_strjoin.c \
	   outils/error_f.c outils/ft_exec.c outils/her_doc.c 
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -I. $(CFLAGS) $(OBJ) -o $(NAME) -lreadline 

%.o: %.c minishell.h
		 $(CC) -I. $(CFLAGS) -c $< -o $@


clean:
		$(RM) $(OBJ) 

fclean: clean
		$(RM) $(NAME)

re: fclean all

