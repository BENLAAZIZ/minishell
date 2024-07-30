/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:31:15 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/30 22:43:12 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <string.h>
# include <fcntl.h>
# include <readline/history.h>
#include <sys/stat.h>
# include <unistd.h>

typedef enum e_type
{
	WORD = 0,
	PIPE = 1,
	L_RED = 2,
	R_RED = 4,
	DL_RED = 5,
	DR_RED = 6,
	AND = 7,
	DAND = 8,
	OPAR = 9,
	CPAR = 10
}	t_type;

typedef struct  s_red_node
{
	char				*file;
	char				*red;
	char				*exp;
	int					expand;
	struct s_red_node	*next;
}	t_red_node;

typedef struct s_cmd_node
{
	char				**command;
	t_red_node			*red_node;
	int					flag_r;
	int					fd_herd;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_word
{
	t_type			type;
	char			*value;
	char			*old_word;
	char			*val_noquotes;
	char			*line;
	int				quotes_type;
	// int				*here_doc_fd;
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;


typedef struct s_path
{
	char			**path;
	char			**cmd_env;
}	t_path;
// **********************


typedef struct s_env
{
	char			*variable;
	char			*value;
	// char			*fil;
	// long			status;
	int				i;
	char 			*expand;
	char			*expansion;
	char			*sub;
	struct s_env	*next;
}	t_env;

typedef struct s_var
{
	char			*var;
	char			*val;
	int				egal;
	char			*fil;
	long			status;
}	t_var;


typedef struct s_variable
{
	t_word		*token;
	t_cmd_node	*node;
	t_cmd_node	*tmp_node;
	t_path		data;
	t_var		var;
	char		*line;
	int			fd[2];
	int 		fd_stdin;
	int 		fd_stdout;
	int			nbr_node;
	int			id;
	int			fd_herd;
}	t_variable;


//expand
void	word_expand_her(t_word *token, t_env *envirment);
// void	desplay_node(t_cmd_node **cmd);
// void	desplay_red_node(t_red_node *redd);
//token_list
int			dollar_length(t_word *token, t_env **envirment);
void		ft_is_expand(t_word *token, t_env *envirment, int *sign, t_variable *varr);
void		expand_her (t_word *token, t_env *envirment);
void		here_doc(char *limiter, char *limiter_nq, t_cmd_node *node, t_env *envirement);
t_word		*ft_list_tokn(char *all_command, t_word *token, t_env *envirment);
t_word		*ft_addlist_token(char *word);
void		ft_lstaddback_token(t_word **list, t_word*new_node);
// int			remove_quotes(t_word *token);
//token_list

//libft
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);

//chech_syntax
int			check_syntax(t_word *token);
int			ft_check_quotes(char c, int *sign);
int			end_point(char c, int *sign);
int			ft_is_space(char c);
char		*check_char(char c);
int			check_quotes(char *line);
int			check_red(int type);
int 		c_after_add(char c);
int 		check_dollar_sign(char c1, char c2, char c3);
// int 		char_stop(char c);
int			char_stop(t_word *token, t_env **envirment);
int 		char_continue(char c);
int			ft_isdigit(int c);
int			is_expand(char c);

//list_function
void		ft_lstclear_token(t_word **list);


//list_files
// void	ft_list_file(t_word	*token, t_red_node **files, t_cmd_node **node, t_env *envirement);
void	ft_list_file(t_word	*token, t_red_node **files, t_cmd_node *node, t_env *envirement);
//listcommands
// void		ft_list_cmd(t_word *token, t_cmd_node **cmd);
void	ft_list_cmd(t_word	*token, t_cmd_node **cmd, t_env *env);
//print error
void		print_error(char *token);
char		*expand_value(char *line);
int			check_char_expand (char c);
void		word_expand (t_word *token, t_env *envirment, t_variable *varr);
// void	ft_is_expand(t_word *token, t_env *envirment, int *sign, t_variable *varr)
//remove_quotes
// int remove_quotes(t_word *token);
int 		remove_quotes(t_word *token, int sign, int i, int j);

int			built_functions(t_env **env, t_var *var,t_variable *varr);
void		echo(char **cmd, int i);
void		unset(t_env **env, char **cmd, t_var *var);
void		ft_env(char **ev, t_env **env);
void		ft_exit(char **cmd, t_var *var);
int			cd(char **cmd, t_env **env);
int			pwd(void);
void		export(t_env **env , char **cmd, int i, t_var *var);
void		display_list_export(t_env *a);
char		*get_variabl_export(char *line, int *egal);

size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s1);
char		*ft_itoa(unsigned int n);
long		ft_atoi(const char *str, t_var *var);
void		*ft_memcpy(void	*dst, const void *src, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);

t_env	*point_node(t_env *env, char *name);
t_env	*ft_lstnew(char *var, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
//================= node ========================

//=========================================
int		size_node(t_cmd_node *a);
int		size_env(t_env *a);
void	display_env(t_env *a);
int		check_env(t_env **env, t_variable *varr);
void	modif_shlvl(t_env **env, t_env *new, char *var, char *val);
void	display_list_export(t_env *a);

char	*get_variabl(char *line);
char	*get_value(char *line);
void	remove_variab(t_env **env, char *name);
char	**ft_splith(char const *s, char c);
void	free_t_split(char **array);
char	*ft_strchr(const char *s, int c);
void	ft_error(char *s, char *flag, int i, int in);
void	close_fd(int *fd);
void	wait_function(int c, t_variable *varr);

int		handle_redirection(int *flag, t_red_node *red_node, int *fd_herd);
void	ft_execute(char **cmd, t_path *data, t_variable *varr);
int		exec_cmd(char **cmd, t_path *data);
char	*get_next_line(int fd);

//free

void	ft_lstclear_red(t_red_node **list);
void	ft_lstclear_cmd(t_cmd_node **list);
#endif