#ifndef MINISHELL
#define MINISHELL

#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <stdio.h>
#include <string.h>
#include <readline/history.h>

 #define PIPE 0
 #define IN_RED  1

typedef struct s_node
{
	int data;
	char **redirection;
	char **command;
	char **com;
	struct s_node	*next;
}t_node;


typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

// typedef struct s_stack
// {
// 	int				content;
// 	int				ord;
// 	struct s_stack	*next;
// } t_stack;
//
char	**ft_splith(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	echo(char **cmd);
void	cd(char **cmd, t_env **env);
void	pwd();
t_env	*ft_lstnew(char *var, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		size_stack(t_env *a);
void	export(t_env **env , char *line);
char	*get_value(char *line);
char	*get_variabl(char *line);
size_t	ft_strlen(const char *s);
t_env 	*point_node(t_env *env, char *name);
void	ft_env(char **ev, t_env **env);
void	display_env(t_env *a);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void	*dst, const void *src, size_t n);
int		ft_atoi(const char *str);
char	*ft_itoa(unsigned int n);
void	display_list_export(t_env *a);

#endif