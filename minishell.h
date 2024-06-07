/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:31:15 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/07 16:24:08 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h>
# include <string.h>
# include <readline/history.h>

typedef struct s_node
{
	char			**redirection;
	char			**command;
	char			**com;
	int				data;
	struct s_node	*next;
}	t_node;

typedef struct s_env
{
	char			*variable;
	char			*value;
	char			*fil;
	long			status;
	struct s_env	*next;
}	t_env;

typedef struct s_var
{
	char	*var;
	char	*val;
	int		egal;
}	t_var;

char	**ft_splith(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	echo(char **cmd);
void	cd(char **cmd, t_env **env);
void	pwd(void);
t_env	*ft_lstnew(char *var, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		size_stack(t_env *a);
void	export(t_env **env , char **cmd);
char	*get_value(char *line);
char	*get_variabl(char *line);
size_t	ft_strlen(const char *s);
t_env	*point_node(t_env *env, char *name);
void	ft_env(char **ev, t_env **env);
void	display_env(t_env *a);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void	*dst, const void *src, size_t n);
long	ft_atoi(const char *str, t_env *env);
char	*ft_itoa(unsigned int n);
void	display_list_export(t_env *a);
void	remove_variab(t_env **env, char *name);
void	unset(t_env **env, char **cmd);
void	ft_exit(char **cmd, t_env	*env);
char	*ft_strjoin(char const *s1, char const *s2);

#endif