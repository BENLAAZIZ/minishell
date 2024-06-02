#include "minishell.h"



void display_env(t_env *a)
{
    while(a)
    {
        printf("%s=%s\n", a->variable, a->value);
        a = a->next;
    }
    printf("\n");
}
void display_list_export(t_env *a)
{
    while(a)
    {
        printf("declare -x %s=\"%s\"\n", a->variable, a->value);
        a = a->next;
    }
    printf("\n");
}


char	*get_variabl(char *line)
{
	int		i;
	char	*variable;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && (line[i] != '='))
		i++;
	variable = (char *)malloc(i + 1);
	if (!variable)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			break ;
		variable[i] = line[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

char	*get_value(char *line)
{
	int		i;
	int		j;
	int		t;
	char	*value;

	i = 0;
	j = 0;
	t = 0;
	if (!line)
		return (NULL);
	while (line[i] && (line[i] != '='))
		i++;
	t = i + 1;
	while (line[++i] != '\0')
		j++;
	value = (char *)malloc(j + 1);
	if (!value)
		return (NULL);
	i = 0;
	while (line[t])
		value[i++] = line[t++];
	value[i] = '\0';
	return (value);
}
t_env 	*point_node(t_env *env, char *name)
{
	t_env	*node;

	node = NULL;
	while (env)
	{
		if (ft_strncmp(env->variable, name, ft_strlen(name)) == 0)
			node = env;
		env = env->next;
	}
	return (node);
}

void	remove_variab(t_env **env, char *name)
{
	t_env	*node;
	t_env	*tmp;
	
	node = point_node(*env, name);
	if (node == NULL)
		return ;
	while (*env)
	{
		if (ft_strncmp((*env)->next->variable, name, ft_strlen(name)) == 0)
		{
			tmp = (*env)->next;
			(*env)->next = (*env)->next->next;
			free(tmp->variable);
			if (tmp->value)
				free(tmp->value);
			return ;
		}
		*env = (*env)->next;
	}
}


void	ft_env(char **ev, t_env **env)
{
	int		i;
	char	*var;
	char	*val;
	t_env	*new;

	i = 0;
	var = NULL;
	val = NULL;
	while (ev[i])
	{
		var = get_variabl(ev[i]);
		val = get_value(ev[i]);
		new = ft_lstnew(var, val);
		ft_lstadd_back(env, new);
		i++;
	}
	remove_variab(env, "PATH");
	remove_variab(env, "PWD");
	new = ft_lstnew("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	ft_lstadd_back(env, new);
	new = ft_lstnew("PWD", getcwd(NULL, 0));
	ft_lstadd_back(env, new);
	new = ft_lstnew("OLDPWD", NULL);
	ft_lstadd_back(env, new);
}

int main(int argc, char* argv[], char **ev)
{
	t_env	*env;
	char	*line = NULL;
	char	**cmd;


	(void)argc;
	(void)argv;
	ft_env(ev, &env);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		add_history(line);
		// rl_redisplay();
		cmd = ft_splith(line, ' ');
		cd(cmd, env);
		free(line);
	}


  	// if ((argc > 1) && (ft_strncmp(argv[1], "cd", 2) == 0))
	// 	cd(argv, &env);
	// else if ((argc > 1) && (ft_strncmp(argv[1], "pwd", 3) == 0))
	// 	pwd();
	// else if ((argc > 1) && (ft_strncmp(argv[1], "export", 6) == 0))
	// {
	// 	export(&env, argv[2]);
	// 	if (argc == 2)
	// 		display_list_export(env);
	// 	else
	// 		display_env(env);
	// }
	// else if ((argc > 1) && (ft_strncmp(argv[1], "env", 3) == 0))
	// 		display_env(env);
	// else 
	// 	echo(argc, argv);
    return 0;
}

