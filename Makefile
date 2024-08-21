
NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

SRC =	builtin/builtins.c builtin/cd.c minishell.c builtin/echo.c builtin/env.c  builtin/env_suit.c \
	 	builtin/export.c builtin/export_ctn.c builtin/pwd.c builtin/unset.c builtin/exit.c \
		outils/spl.c outils/list_h.c outils/ft_init_h.c \
	 	outils/error_f.c outils/ft_exec.c outils/her_doc.c  outils/redirection.c outils/exec_line.c outils/clear_list.c \
		pars/check_line.c pars/expand.c pars/ft_add_list_token.c pars/ft_check_syntax.c pars/ft_list_cmd.c pars/list_files.c \
		pars/ft_substr.c pars/list_function.c \
		pars/remove_quotes.c pars/ft_list_token.c pars/ft_list_token2.c pars/signals.c pars/utils.c pars/expand_utils.c  pars/expand_utils2.c \
		pars/expand_hdoc.c pars/expand_hdoc_utils.c pars/expand_hdoc_utils2.c pars/puts_error_syntax.c \
		pars/check_char.c pars/check_char2.c pars/list_cmd_utils.c \
		libft/ft_atoi_h.c libft/ft_itoa_h.c libft/ft_strjoin.c libft/ft_strncmp.c \
	 libft/ft_strchr.c libft/ft_strdup.c libft/ft_strcmp.c libft/ft_split.c

OBJ = $(SRC:.c=.o)   

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L $(READLINE_L) -lreadline 

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(READLINE_I)


clean:
	$(RM) $(OBJ) 

fclean: clean
	$(RM) $(NAME)

re: fclean all
