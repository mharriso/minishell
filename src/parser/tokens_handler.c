#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"
#include "parser.h"
#include "env_func.h"
#include "com_func.h"
#include "red_func.h"
#include "structs.h"

static unsigned int	g_ret;

typedef struct s_str
{
	char		*data;
	size_t		len;
}				t_str;

// void	pritn_com(void *com)
// {
// 	t_command	*cmd;
// 	int			i;

// 	cmd = com;
// 	i = 0;
// 	while ((cmd->com)[i])
// 	{
// 		printf("cmd = |%s|\n",(cmd->com)[i]);
// 		i++;
// 	}
// }

char	*get_env_name(char	**src)
{
	char	*name;
	int		i;

	i = 0;
	while (ft_isalnum((*src)[i]) || (*src)[i] == '_')
		i++;
	name = malloc(i + 1);
	if (!name)
		error_exit("malloc error");
	i = 0;
	while (ft_isalnum(**src) || **src == '_')
	{
		name[i] = **src;
		(*src)++;
		i++;
	}
	name[i] = '\0';
	return (name);
}

void	add_env_value(t_str *str, char **src, t_list **env)
{
	char	*name;
	char	*value;
	size_t	value_len;

	value = NULL;
	if (**src == '?')
	{
		(*src)++;
		value = ft_itoa(g_ret);
		if (!value)
			error_exit("malloc error");
	}
	else if (ft_isalpha(**src) || **src == '_')
	{
		name = get_env_name(src);
		value = env_getvaluebyname(name, *env);
		if (value)
			value = ft_strdup(value);
		free(name);
	}
	if (value)
	{
		value_len = ft_strlen(value);
		str->data = ft_realloc(str->data, str->len, str->len + value_len + 1);
		ft_memcpy(str->data + str->len, value, value_len);
		str->len += value_len;
		free(value);
	}
}

char	*create_env_str(char *src, t_list **env)
{
	t_str	str;
	char	*dollar;
	int		part_len;

	dollar = ft_strchr(src, '$');
	str.data = ft_strdup("");
	str.len = 0;
	while (dollar)
	{
		part_len = dollar - src;
		str.data = ft_realloc(str.data, str.len, str.len + part_len + 1);
		ft_memcpy(str.data + str.len, src, part_len);
		str.len += part_len;
		src = dollar + 1;
		add_env_value(&str, &src, env);
		dollar = ft_strchr(src, '$');
	}
	part_len = ft_strlen(src);
	str.data = ft_realloc(str.data, str.len, str.len + part_len + 1);
	ft_memcpy(str.data + str.len, src, part_len + 1);
	return (str.data);
}

char	*create_str(t_token *tokens)
{
	char	*str;

	str = malloc(tokens->len + 1);
	if (!str)
		error_exit("malloc error");
	ft_memcpy(str, tokens->data, tokens->len + 1);
	return (str);
}

// char	*type(int type) //delete
// {
// 	if (type == EMPTY)
// 		return ft_strdup("EMPTY");
// 	else if (type == TEXT)
// 		return ft_strdup("TEXT");
// 	else if (type ==  RED_RIGHT)
// 		return ft_strdup("RED_RIGHT");
// 	else if (type ==  RED_DRIGHT)
// 		return ft_strdup("RED_DRIGHT");
// 	else if (type ==  RED_LEFT)
// 		return ft_strdup("RED_LEFT");
// 	else if (type == PIPE)
// 		return ft_strdup("PIPE");
// 	else if (type == SEMICOLON)
// 		return ft_strdup("SEMICOLON");
// 	else if (type == OR)
// 		return ft_strdup("OR");
// 	else if (type == AND)
// 		return ft_strdup("AND");
// 	else if (type == ENV)
// 		return ft_strdup("ENV");
// 	else
// 		return ft_strdup("ERROR TYPE");
// }

// void	print_tokens(t_token *lst)
// {
// 	printf("   TOKENS\n");
// 	while (lst)
// 	{
// 		printf("%-11s:  %s\n", type(lst->type), lst->data);
// 		lst = lst->prev;
// 	}
// 	printf("\n\n");
// }

void	init_cmd(t_command **cmd)
{
	*cmd = malloc(sizeof(t_command));
	if (!*cmd)
		error_exit("init_cmd\n");
	ft_memset(*cmd, 0, sizeof(t_command));
}

void	fill_arrays(t_command *cmd, t_token **tokens, t_list **env)
{
	int		i;
	int		j;
	char	*filename;

	i = 0;
	j = 0;
	while (*tokens && (*tokens)->type != SEMICOLON && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == ENV)
			cmd->com[j++] = create_env_str((*tokens)->data, env);
		else if ((*tokens)->type == TEXT)
			cmd->com[j++] = create_str(*tokens);
		else if ((*tokens)->type <= RED_DRIGHT)
		{
			*tokens = (*tokens)->prev;
			if ((*tokens)->type == ENV)
				filename = create_env_str((*tokens)->data, env);
			else if ((*tokens)->type == TEXT)
				filename = create_str(*tokens);
			cmd->red[i++] = red_create(filename, (*tokens)->next->type);
		}
		*tokens = (*tokens)->prev;
	}
	// printf("\nCOMMANDS ARRAY\n");
	// for (size_t k = 0; cmd->com[k]; k++) // delete !!!
	// 	printf("%s\n", cmd->com[k]);
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
		if (temp->type >= TEXT)
			c_size++;
		temp = temp->prev;
	}
	//printf("COM_SIZE = %d\nRED_SIZE = %d\n", c_size, r_size);
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
	while (*tokens && ((*tokens)->type != SEMICOLON))
	{
		init_cmd(&cmd);
		alloc_arrays(cmd, *tokens);
		fill_arrays(cmd, tokens, env);
		set_pipe(cmd, *tokens);
		node = ft_lstnew(cmd);
		ft_lstadd_back(&commands, node);
		if (*tokens)
			*tokens = (*tokens)->prev;
	}
	if (*tokens && ((*tokens)->type == SEMICOLON))
		*tokens = (*tokens)->prev;
	return (commands);
}

int	tokens_handler(t_token **tokens, t_list **env)
{
	t_list		*commands;
	t_token		*end;

	commands = *env;
	end = *tokens;
	while (*tokens)
	{
		commands = create_com_lst(tokens, env);
		if (commands)
		{
			g_ret = commands_handler(commands, env);
			ft_lstclear(&commands, com_clear);
		}
	}
	clear_tokens_prev(&end, free);
	return (g_ret);
}

