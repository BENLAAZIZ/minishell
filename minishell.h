/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:31:15 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/07 16:56:47 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <readline/history.h>



typedef struct s_cmd
{
	char			**command;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_red
{
	char			*red;
	char			*type;
	struct s_red	*next;
}	t_red;


typedef struct s_node
{
	t_cmd			**cmd_node;
	t_red			*red_node;
	struct s_node	*next;
}	t_node;



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

// typedef struct s_pipe
// {
// 	int		fd[2];
// 	int		i;
// 	int		argc;
// 	char	**envv;
// 	int		in_tmp;
// 	pid_t	pid;
// }	t_pipe;

void	echo(char **cmd);
void	unset(t_env **env, char **cmd, t_var *var);
void	ft_env(char **ev, t_env **env);
void	ft_exit(char **cmd, t_var *var);
int		cd(char **cmd, t_env **env);
int		pwd(void);
int		export(t_env **env , char **cmd);

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_itoa(unsigned int n);
long	ft_atoi(const char *str, t_var *var);
void	*ft_memcpy(void	*dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

t_env	*point_node(t_env *env, char *name);
t_env	*ft_lstnew(char *var, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		size_pipe_node(t_node *a);
int		size_env(t_env *a);
void	display_env(t_env *a);
void	display_list_export(t_env *a);

char	*get_variabl(char *line);
char	*get_value(char *line);
void	remove_variab(t_env **env, char *name);
char	**ft_splith(char const *s, char c);
void	free_t_split(char **array);
char	*ft_strchr(const char *s, int c);
void	ft_error(char *s, char *flag, int i, int in);
void	close_fd(int *fd);

void	ft_exuctute(char **cmd, t_path *data, t_var *var);
int		exec_cmd(char **cmd, t_path *data);
char	*get_next_line(int fd);


#endif