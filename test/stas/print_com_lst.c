void	print_com_list(t_list *com_lst)
{
	char **cmd;

	while (com_lst)
	{
		cmd = com_getcom(com_lst);
		printf("Commands:\n");
		while (*cmd)
		{
			printf("|%s|\n", *cmd);
			cmd++;
		}
		if (!com_getinfo(com_lst))
			printf("Info null\n");
		if (!com_getredir(com_lst))
			printf("red null\n");
		printf("pipe = %d\n\n", com_getptype(com_lst));
		com_lst = com_lst->next;
	}
}
