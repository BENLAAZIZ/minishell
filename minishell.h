/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:31:15 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/04 17:03:07 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <termios.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	CPAR = 10,
	CM_NF = 11,
	NO_F = 12,
	IS_D = 13,
	PRM_D = 14,
	OMB_R = 15,
	NO_V = 16,
	UNS = 17,
	EXT = 18
}	t_type;

typedef struct s_red_node
{
	char				*file;
	char				*red;
	char				*exp;
	int					expand;
	struct s_red_node	*next;
}						t_red_node;

typedef struct s_node
{
	char				**command;
	int					flag_r;
	int					fd_herd;
	t_red_node			*red_node;
	struct s_node		*next;
}						t_node;

typedef struct s_word
{
	t_type			type;
	char			*value;
	char			*old_word;
	char			*val_noquotes;
	char			*line;
	int				quotes_type;
	int				is_expand;
	char			**split_value;
	struct s_word	*next;
	struct s_word	*prev;
}					t_word;

typedef struct s_path
{
	char	**path;
	char	**cmd_env;
}			t_path;

typedef struct s_env
{
	char			*variable;
	char			*value;
	int				i;
	char			*expand;
	int				status;
	char			*expansion;
	char			*sub;
	struct s_env	*next;
}					t_env;

typedef struct s_var
{
	char	*var;
	char	*val;
	int		egal;
	char	*fil;
	long	status;
}			t_var;

typedef struct s_variable
{
	t_word		*token;
	t_node		*node;
	t_node		*tmp_node;
	t_path		data;
	t_var		var;
	char		*line;
	int			pid;
	int			fd[2];
	int			fd_stdin;
	int			fd_stdout;
	int			nbr_node;
	int			id;
}				t_variable;

// ===================== list_cmds  ============================
t_node	*ft_lstaddback_cmd(t_node **list, t_node *new_node);
t_node	*ft_addnode_cmds(char **commands);
// ===================== check_syntax  =========================
void	ft_puterror(char *token);
int		check_token(int type);
int		return_error(t_word *token);
int		check_after_d(char c);
int		end_point(char c, int *sign);
int		c_after_add(char c);
// =====	================ expand_her  ===========================
int		dollar_length_her(t_word *token, t_env **env);
char	*cpy_the_rest_2(t_word *token, t_env **env, int *sign, int old_i);
int		char_stop_her(t_word *token, t_env **env);
char	*copy_the_rest_her(t_word *token, t_env *env, int *sign);
char	*sp_case_helper_hdoc(t_word *token, t_env *env);
char	*spcase_cpy_hdoc(t_word *token, t_env *env, int *sign);
void	ft_add_q_her(t_env **env_node);
char	*rephdoc_helper(t_word *token, t_env **env, t_env *env_node, int *sign);
char	*replace_her(t_word *token, t_env *env, t_env *env_node, int *sign);
// ===================== expand  ===============================

t_word	*ft_list_tokn(char *all_command, t_word *token, t_env *env);
t_word	*ft_addlist_token(char *word);
void	word_expand_her(t_word *token, t_env *env);
void	here_doc(char *limiter, char *limiter_nq, t_node *node, t_env *env);
void	ft_lstaddback_token(t_word **list, t_word*new_node);
int		dollar_length(t_word *token, t_env **env);
char	*replace_helper(t_word *token, t_env **env, t_env *env_node, int *sign);
char	*replace(t_word *token, t_env *env, t_env *env_node, int *sign);
void	ft_add_q(t_env **env_node);
char	*copy_the_rest(t_word *token, t_env *env, int *sign);
char	*copy_the_rest_2(t_word *token, t_env **env, int *sign, int old_i);
int		is_expand(char c);
char	*spcase_cp(t_word *token, t_env *env, int *sign, t_variable *data);
char	*sp_case_helper(t_word *token, t_env *env, t_variable *data);
char	*copy_the_rest(t_word *token, t_env *env, int *sign);
void	ft_add_q(t_env **env_node);

// ===================== chech_syntax  ===============================

void	word_expand(t_word *token, t_env *env, t_variable *varr);
char	*get_var(char *line);
char	*check_char(char c);
int		check_syntax(t_word *token);
int		ft_check_quotes(char c, int *sign);
int		end_point(char c, int *sign);
int		ft_is_space(char c);
int		check_quotes(char *line);
int		check_red(int type);
int		c_after_add(char c);
int		check_dollar_sign(char c1, char c2, char c3);
int		char_stop(t_word *token, t_env **env);
int		char_continue(char c);
int		ft_isdigit(int c);
int		is_expand(char c);
int		check_char_expand(char c);
int		remove_quotes(t_word *token, int sign, int i, int j);

// ======================== builtin =============================

void	echo(char **cmd, int i, t_variable *varr);
void	unset(t_env **env, char **cmd, t_var *var);
void	ft_env(char **ev, t_env **env);
void	ft_exit(char **cmd, t_var *var, t_env **env);
void	export(t_env **env, char **cmd, int i, t_var *var);
void	display_list_export(t_env *a);
void	get_cmd_env(t_env *env, t_path *data, int *i);
void	display_env(t_env *a);
void	modif_shlvl(t_env **env, t_env *new, char *var, char *val);
void	display_list_export(t_env *a);
char	*get_variabl_export(char *line, int *egal);
int		built_functions(t_env **env, t_var *var, t_variable *varr);
int		cd(char **cmd, t_env **env);
int		pwd(void);
int		check_env(t_env **env, t_variable *varr);

// ===================== env list  ========================

t_env	*point_node(t_env *env, char *name);
t_env	*ft_lstnew(char *var, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		size_env(t_env *a);
void	ft_lstclear_env(t_env **env);

// ===================== execution  ===============================

void	ft_execute(char **cmd, t_path *data, t_variable *varr);
void	in_child_process(t_env **env, t_variable *varr);
void	make_all_process(t_env **env, t_variable *varr, int c);
int		make_one_process(t_env **env, t_variable *varr);
int		check_redirection(t_variable *varr);
int		execute_line(t_env **env, t_variable *varr);
int		handle_redirection(int *flag, t_red_node *red_node, int *fd_herd);
int		exec_cmd(char **cmd, t_path *data);

// ===================== list pipe  ===============================

void	list_file(t_word *token, t_red_node **files, t_node *node, t_env *env);
void	ft_list_cmd(t_word	*token, t_node **cmd, t_env *env);
int		size_node(t_node *a);

// ===================== LIBFT  ===============================

size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c, int sign);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_splith(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_itoa(unsigned int n);
long	ft_atoi(const char *str, t_var *var);
void	*ft_memcpy(void	*dst, const void *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_countword(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// ===================== signls  ===============================
int		signal_hdoc(int check);
void	handle_siginit(int sig);
void	restore_terminal_attributes(struct termios *original_termios);
void	get_terminal_attr(struct termios *original_termios);
void	signal_in_child(int sig);

//================= outil ========================

char	*get_variabl(char *line);
char	*get_value(char *line);
void	remove_variab(t_env **env, char *name);
void	ft_error(char *s, char *flag, int i, int in);
void	wait_function(int c, t_variable *varr);

// ======================== error && free =============================

void	ft_builtin_error(char *error, int flag, int i);
void	ft_perror_h(char *error, int flag);
void	print_error(char *token);
void	free_data(t_variable *varr);
void	free_t_split(char **array);
void	ft_lstclear_token(t_word **list);
void	ft_lstclear_red(t_red_node **list);
void	ft_lstclear_cmd(t_node **list);

#endif