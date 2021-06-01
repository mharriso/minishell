#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"
#include "parser.h"
#include "env_func.h"
#include "com_func.h"
#include "red_func.h"
#include "structs.h"

static unsigned int g_ret;

typedef struct s_count
{
	int red;
	int com;
}				t_count;

// char *get_env_name(t_token *tokens)
// {
// 	char	*name;
// 	char	c;
// 	int		res;
// 	int		i;

// 	name = malloc(tokens->len);
// 	if(!name)
// 		error_exit("malloc error");
// 	c = (*(line->data))[line->index];
// 	i = 0;
// 	while(1)
// 	{
// 		res = ft_isalnum(c) || c == '_';
// 		if(!c || !res)
// 			break ;
// 		name[i] = c;
// 		c = (*(line->data))[++line->index];
// 		i++;
// 	}
// 	name[i] = '\0';
// 	return (name);
// }

void	create_ret_str(t_token **tokens)
{
	char	*str_ret;
	char	*tmp;

	str_ret = ft_itoa(g_ret);
	tmp = ft_strjoin((*tokens)->data, str_ret);
	free((*tokens)->data);
	(*tokens)->data = tmp;
	(*tokens)->len += ft_strlen(str_ret);
	free(str_ret);
}

char	*create_env_str(t_token *tokens, t_list **env)
{
	char	*name;
	char	*value;
	char	*str;
	int		i;


	str = malloc(tokens->len + 1);
	if(!str)
		error_exit("malloc error");
	i = 0;
	while(*(tokens->data))
	{
		str[i] = *(tokens->data);
	}

	if(*(tokens->data) == '?');
		value = ft_itoa(g_ret);


	name = get_env_name(tokens->data);
	value = env_getvaluebyname(name, *env);
	free(name);

}


char	*create_str(t_token *tokens)
{
	char	*str;

	str = malloc(tokens->len + 1);
	ft_memcpy(str, tokens->data, tokens->len + 1);
	return (str);
}
char	**create_com_array(t_token **tokens, t_list **env)
{
	char	**array;
	size_t	size;

	size = 0;
	while ((*tokens) && (*tokens)->type > TEXT)
	{
		size++;
		*tokens = (*tokens)->prev;
	}
	array = malloc((size + 1) * sizeof(char *));
	if(!size || array)
		return(NULL);
	array[size] = NULL;
	while (size)
	{
		if((*tokens)->type == TEXT)
			array[--size] = create_str(*tokens);
		// else if((*tokens)->type == ENV)
		// 	array[--size] = create_env_str(*tokens, env);
		*tokens = (*tokens)->next;
	}
	return (array);

}

t_list	*create_com_lst(t_token **tokens, t_list **env)
{
	int	pipe_type;
	t_redir		*red;
	t_list		*node;
	t_command	*cmd;
	char		**com_array;

	t_list		*list_to_return;
	t_token		*temp;
	int			size;
	int			rsize;
	int			i;
	int			j;

	pipe_type = 0;
	list_to_return = NULL;
	while(*tokens && ((*tokens)->type =! SEMICOLON))
	{
		temp = *tokens;
		rsize = 0;
		while (*tokens && temp->type != SEMICOLON && temp->type != PIPE)
		{
			if ((*tokens)->type <= RED_DRIGHT)
				rsize++;
			temp = temp->prev;
		}
		if (rsize)
		{
			red = malloc(sizeof(t_redir) * rsize + 1);
			temp = *tokens;
			size = 0;
			while (temp->type == TEXT)
			{
				size++;
				temp = temp->prev;
			}
			size -= rsize;
			com_array = malloc(sizeof(char *) * size + 1);
			com_array[size] = NULL;
			i = 0;
			j = 0;
			while ((*tokens)->type != SEMICOLON && (*tokens)->type != PIPE)
			{
				if ((*tokens)->type <= RED_DRIGHT)
				{
					*tokens = (*tokens)->prev;
					red[i] = red_create((*tokens)->data,(*tokens)->next->type);
					*tokens = (*tokens)->prev;
				}
				while ((*tokens)->type == TEXT)
				{
					com_array[j] = ft_strdup((*tokens)->data);
					j++;
					*tokens = (*tokens)->prev;
				}
			}
			red[i] = red_create_last();

			if (pipe_type & PIPE_OUT)
					pipe_type |= PIPE_IN;
			if ((*tokens)->type == PIPE)
				pipe_type |= PIPE_OUT;
			else
				pipe_type &= ~PIPE_OUT;

			cmd = com_create(com_array, red, pipe_type);
			node = ft_lstnew(cmd);
			ft_lstadd_back(&list_to_return, node);
		}
		else if ((*tokens)->type == TEXT)
		{
			temp = *tokens;
			size = 0;
			while (temp->type == TEXT)
			{
				size++;
				temp = temp->prev;
			}
			com_array = malloc(sizeof(char *) * size + 1);
			com_array[size] = NULL;
			i = 0;
			while (i < size)
			{
				com_array[i] = ft_strdup((*tokens)->data);
				i++;
				*tokens = (*tokens)->prev;
			}

			if (pipe_type & PIPE_OUT)
					pipe_type |= PIPE_IN;

			if ((*tokens)->type == PIPE)
				pipe_type |= PIPE_OUT;
			else
				pipe_type &= ~PIPE_OUT;

			cmd = com_create(com_array, NULL, pipe_type);
			node = ft_lstnew(cmd);
			ft_lstadd_back(&list_to_return, node);
		}
	}
	return (list_to_return);
}

void	tokens_handler(t_token **tokens, t_list **env)
{
	t_list		*commands;

	while (*tokens)
	{
		//get_env()
		commands = create_com_lst(tokens, env);
		commands_handler(commands, env);

		if (*tokens && (*tokens)->prev)
		{
			*tokens = (*tokens)->prev;
			// clear_tokens(&((*tokens)->next), free); del by next!!!!
		}
		ft_lstclear(&commands, com_clear);
	}
	// clear_tokens(tokens, free); del by next!!!!
}

