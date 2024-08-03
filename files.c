

void	display_red(t_red_node *red)
{
	if (!red)
		return;
		while (red)
		{
			printf("\n [%s %s] ", red->red, red->file);
			red = red->next;
		}
		
}

void	display_node(t_cmd_node *node)
{
	if (!node)
	{
		printf("khaaaawya mafiha walo\n");
		return;
	}
		while (node)
		{
			printf("\n-----------------------------------\n");
			display_red(node->red_node);
			printf("\n {%s} ", node->command[0]);
			printf("\n-----------------------------------\n");
			node = node->next;
		}
		
}