# NAME = minishell

# CC = cc

# CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

# RM = rm -f



# SRC =  builtin/builtins.c builtin/cd.c minishell.c outils/spl.c outils/list_h.c  builtin/echo.c builtin/env.c \
# 	  builtin/export.c builtin/pwd.c builtin/unset.c outils/ft_atoi_h.c outils/ft_itoa_h.c builtin/exit.c outils/ft_strjoin_h.c \
# 	   outils/error_f.c outils/ft_exec.c outils/her_doc.c \
# 	   pars/check_line.c pars/expand.c pars/ft_add_list_token.c pars/ft_check_syntax.c pars/ft_list_cmd.c pars/ft_list_files.c \
# 	   pars/ft_split.c pars/ft_strcmp.c pars/ft_substr.c pars/list_function.c pars/make_space.c \
# 	   pars/remove_quotes.c pars/ft_list_token.c
# OBJ = $(SRC:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) -I. $(CFLAGS) $(OBJ) -o $(NAME) -lreadline 

# %.o: %.c minishell.h
# 		 $(CC) -I. $(CFLAGS) -c $< -o $@


# clean:
# 		$(RM) $(OBJ) 

# fclean: clean
# 		$(RM) $(NAME)

# re: fclean all

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

RM = rm -f

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

SRC =  builtin/builtins.c builtin/cd.c minishell.c outils/spl.c outils/list_h.c  builtin/echo.c builtin/env.c \
	  builtin/export.c builtin/pwd.c builtin/unset.c outils/ft_atoi_h.c outils/ft_itoa_h.c builtin/exit.c outils/ft_strjoin_h.c \
	   outils/error_f.c outils/ft_exec.c outils/her_doc.c \
	   pars/check_line.c pars/expand.c pars/ft_add_list_token.c pars/ft_check_syntax.c pars/ft_list_cmd.c pars/ft_list_files.c \
	   pars/ft_split.c pars/ft_strcmp.c pars/ft_substr.c pars/list_function.c pars/make_space.c \
	   pars/remove_quotes.c pars/ft_list_token.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -I. $(CFLAGS) $(OBJ) -o $(NAME) -L $(READLINE_L) -lreadline 

%.o: %.c minishell.h
	$(CC) -I. $(CFLAGS) -c $< -o $@ -I $(READLINE_I)


clean:
	$(RM) $(OBJ) 

fclean: clean
	$(RM) $(NAME)

re: fclean all
