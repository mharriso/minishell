#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"
#include "parser.h"
#include "env_func.h"
#include "com_func.h"
#include "red_func.h"
#include "structs.h"

void	init_cmd(t_command **cmd)
{
	*cmd = malloc(sizeof(t_command));
	if (!*cmd)
		error_exit("init_cmd\n");
	ft_memset(*cmd, 0, sizeof(t_command));
}

void	fill_arrays(t_command *cmd, t_token **tokens)
{
	int		i;
	int		j;
	char	*filename;

	i = 0;
	j = 0;
	while (*tokens && (*tokens)->type != SEMICOLON && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type & WORD)
			cmd->com[j++] = create_str(*tokens);
		else if ((*tokens)->type <= RED_DRIGHT)
		{
			*tokens = (*tokens)->prev;
			if ((*tokens)->type & WORD)
				filename = create_str(*tokens);
			cmd->red[i++] = red_create(filename, (*tokens)->next->type);
		}
		*tokens = (*tokens)->prev;
	}
}

void	alloc_arrays(t_command *cmd, t_token *tokens)
{
	t_token		*temp;
	int			c_size;
	int			r_size;

	temp = tokens;
	r_size = 0;
	c_size = 0;
	while (temp && temp->type != SEMICOLON && temp->type != PIPE)
	{
		if (temp->type <= RED_DRIGHT)
			r_size++;
		if (temp->type & WORD)
			c_size++;
		temp = temp->prev;
	}
	if (r_size)
	{
		cmd->red = malloc(sizeof(t_redir) * (r_size + 1));
		cmd->red[r_size] = red_create_last();
		c_size -= r_size;
	}
	cmd->com = malloc(sizeof(char *) * (c_size + 1));
	cmd->com[c_size] = NULL;
}

void	set_pipe(t_command *cmd, t_token *tokens)
{
	static int	type;

	if (type & PIPE_OUT)
		cmd->pipe_type |= PIPE_IN;
	if (tokens && tokens->type == PIPE)
		cmd->pipe_type |= PIPE_OUT;
	else
		cmd->pipe_type &= ~PIPE_OUT;
	type = cmd->pipe_type;
}

t_list	*create_com_lst(t_token **tokens, t_list **env)
{
	t_list		*node;
	t_command	*cmd;
	t_list		*commands;

	commands = NULL;
	env = NULL;
	while (*tokens && ((*tokens)->type != SEMICOLON))
	{
		init_cmd(&cmd);
		alloc_arrays(cmd, *tokens);
		fill_arrays(cmd, tokens);
		set_pipe(cmd, *tokens);
		node = ft_lstnew(cmd);
		ft_lstadd_back(&commands, node);
		if (*tokens)
			*tokens = (*tokens)->prev;
	}
	if (*tokens && ((*tokens)->type == SEMICOLON))
	{
		*tokens = (*tokens)->prev;
		clear_tokens_next(&((*tokens)->next), free);
	}
	return (commands);
}
