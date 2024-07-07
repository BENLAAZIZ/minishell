NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

SRC =  builtin/builtins.c builtin/cd.c minishell.c spl.c list.c  builtin/echo.c builtin/env.c \
	  builtin/export.c builtin/pwd.c builtin/unset.c ft_atoi.c ft_itoa.c builtin/exit.c ft_strjoin.c \
	   error_f.c ft_exec.c her_doc.c 
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

