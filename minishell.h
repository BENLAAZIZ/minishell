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

void	ft_addto_node(char *line, t_node *node);
int		ft_minishell(char *line);
void	ft_lstclear(t_node **list);
t_node	*ft_addlist(char *cmd, int j);
void	ft_lstaddback(t_node **list, t_node *new_node);
int		ft_lstsize(t_node *stack_a);
char	**ft_split(char const *s, char c);
int		ft_countword(char const *s, char c);
int		ft_check_quotes(char c, int *sign);

//
char	**ft_splith(char const *s, char c);


#endif