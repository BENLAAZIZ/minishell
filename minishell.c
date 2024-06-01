#include "minishell.h"



void display_list(t_env *a)
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


void	ft_env(char **env, t_env **envv)
{
	int		i;
	char	*var;
	char	*val;
	t_env	*new;

	i = 0;
	var = NULL;
	val = NULL;
	while (env[i])
	{
		var = get_variabl(env[i]);
		val = get_value(env[i]);
		new = ft_lstnew(var, val);
		ft_lstadd_back(envv, new);
		i++;
	}
}

int main(int argc, char* argv[], char **env)
{
	t_env	*envv;

	ft_env(env, &envv);
  	if ((argc > 1) && (ft_strncmp(argv[1], "cd", 2) == 0))
		cd(argv, &envv);
	else if ((argc > 1) && (ft_strncmp(argv[1], "pwd", 3) == 0))
		pwd();
	else if ((argc > 1) && (ft_strncmp(argv[1], "export", 6) == 0))
	{
		export(&envv, argv[2]);
		if (argc == 2)
			display_list_export(envv);
		else
			display_list(envv);
	}
	else if ((argc > 1) && (ft_strncmp(argv[1], "env", 6) == 0))
			display_list(envv);
	else 
		echo(argc, argv);
    return 0;
}

