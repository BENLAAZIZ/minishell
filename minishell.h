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
void	echo(int argc, char **argv);
void	cd(char **cmd, t_env *env);
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

#endif