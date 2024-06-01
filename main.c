#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <stdio.h>

int ft_check_quotes(char c, int *sign)
{
	if (c == '"' && *sign == 1)
		*sign = 0;
	else if (c == '\'' && *sign == 2)
		*sign = 0;
	else if (c == '"')
		*sign = 1;
	else if (c == '\'')
		*sign = 2;
	return (0);
}

void ft_add_red(t_node *node)
{
	int j = 0;
	int i = 0;
	t_node *tmp;

	tmp = node;
	while(node)
	{
		j = 0;
		i = 0;
		while (node->command[j])
		{
			printf("......... %s\n",node->command[j]);
			if (node->command[j][0] == '>')
			{
				puts("wah");
				node->data = 1;
				node->next->data = 1; 
				node->redirection[i] = node->command[j];
				puts("ewa");
				i++;
				node->next->redirection[i] = node->command[j];
				i++;
			}
			j++;
		}
		node = node->next;
	}
	node = tmp;
}

// void ft_add_com(t_node *node)
// {
// 	printf("hh");
// 	int j = 0;
// 	int i = 0;
// 	t_node *tmp;

// 	tmp = node;
// 	while(node->next)
// 	{
// 		if (node->data == 0)
// 		{
// 			node->com[j] = node->command[i];
// 			j++;
// 		}
// 		i++;
// 		node = node->next;
// 	}
// 	node = tmp;
// }
void ft_addto_node(char *line, t_node *node)
{
	char **commands;

	if (*line == '\0')
		return;
	int i = 0;
	int j = 0;
	int x = 0;
	int size = 0;
	char **cmd;
	char line_copy[265];//1 
	while (line[i] != '\0')
	{
		if (line[i] == '<' || line[i] == '>' && (line[i - 1] != ' ' || line[i - 1] != '\t'))
		{
			line_copy[j] = ' ';
			j++;
		}
		if (line[i] == '<' || line[i] == '>' && (line[i + 1] != ' ' || line[i + 1] != '\t'))
		{
			line_copy[j++] = line[i++];
			line_copy[j] = ' ';
			j++;
		}
		line_copy[j] = line[i];
		j++;
		i++;
	}
	line_copy[j] = '\0';
	t_node *command;
	i = 0;
	j = 0;
	commands = ft_split(line_copy, '|');
	int p = 0;
	// while (commands[p])
	// {
	// 	printf("{%s}\n", commands[p]);
	// 	p++;
	// }
	cmd = (char **)malloc(sizeof(char *) * 3);
	while (commands[i] != NULL)
	{
		j = 0;
		size = 0;
		x = 0;
		while (commands[i][j] != '\0')
		{
			while(commands[i][size] != '\0')
				size++;
			if (size != 0 && x == 0)
			{
				cmd[i] = malloc(size + 1);
				if (!cmd)
					break;
				while (x < size)
				{
					cmd[i][x] = commands[i][x];
					x++;
				}
			}
			j++;
		}
		command = ft_addlist(cmd[i], size);
		ft_lstaddback(&node, command);
		i++;
	}

	node->redirection = NULL;
	ft_add_red(node);
	// ft_add_com(node);
	// exit(0);
	t_node *tmp = node;
	while (node != NULL)
	{
		p = 0;
		puts("zozo");
		if (node->redirection != NULL)
		{
			while (node->redirection[p])
			{
				puts("ok");
				printf("{%s}\n", node->redirection[p]);
				p++;
			}
		}
		printf("\n");
		node = node->next;
	}
	node = tmp;
}

int	ft_check_line(char *line)
{
	int	i;
	int	sign;
	int	size;

	size = 0;
	sign = 0;
	i = 0;
	while (line[i] != '\0')
	{
		ft_check_quotes(line[i], &sign);
		if (line[i] == ' ')
		{
			while (line[i] == ' ' || line[i] == '\t')
				i++;
		}
		if (line[i])
			size++;
		if (line[i] == '|' && size == 1)
			return(write(1, "syntax error near unexpected token `|'\n", 39), 1);
		if (line[i] == '|')
		{
			i++;
			while(line[i] == ' ' || line[i] == '\t')
				i++;
			if(size == 1 || (line[i] == '|' && sign == 0) || line[i] == '\0')
				return(write(1, "syntax error near unexpected token `|'\n", 39), 1);
		}
		i++;
	}
	if (sign != 0)
		return (write(1, "Error\n", 6), 1);
	
	puts("ok");
	return (0);
}
int ft_minishell(char *line)
{
	t_node *node = NULL;
	int p = 0;
	while (1)
	{
		p = 0;
		line = readline("minishell$ ");
		if (!line)
			break;
		add_history(line);
		rl_redisplay();
		printf("%s", "test");
		ft_check_line(line);
		ft_addto_node(line, node);
		while (node != NULL)
		{
			printf("redirection {%s}\n", node->com[p]);
			p++;
		}
	}
	return(0);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	char	*line = NULL;
	ft_minishell(line);
}