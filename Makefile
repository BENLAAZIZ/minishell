NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

SRC =  builtins.c minishell.c spl.c list.c cd.c echo.c env.c \
	  export.c pwd.c unset.c ft_atoi.c ft_itoa.c exit.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline 

%.o: %.c minishell.h
		 $(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJ) 

fclean: clean
		$(RM) $(NAME)

re: fclean all

