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

typedef struct s_str
{
	char		*data;
	size_t		len;
}				t_str;

char *get_env_name(char	**src)
{
	char	*name;
	int		i;

	name = malloc(100); // FIX
	if(!name)
		error_exit("malloc error");
	i = 0;
	while(ft_isalnum(**src) || **src == '_')
	{
		name[i] = **src;
		(*src)++;
		i++;
	}
	name[i] = '\0';
	return (name);
}

void		add_env_value(t_str *str, char **src, t_list **env)
{
	char	*name;
	char	*value;
	size_t	value_len;

	value = NULL;
	if(**src == '?')
	{
		value = ft_itoa(g_ret);
		if(!value)
			error_exit("malloc error");
	}
	else if(ft_isalpha(**src) || **src == '_')
	{
		name = get_env_name(src);
		value = ft_strdup(env_getvaluebyname(name, *env));
		//printf("name = |%s| value = %s\n", name, value);
		free(name);
	}
	if(value)
	{
		value_len = ft_strlen(value);
		str->data = ft_realloc(str->data, str->len, str->len + value_len + 1);
		str->len += value_len + 1;
		ft_memcpy(str->data, value, value_len);
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
	while(dollar)
	{
		part_len = dollar - src;
		str.data = ft_realloc(str.data, str.len, str.len + part_len + 1);
		str.len += part_len;
		ft_memcpy(str.data, src, part_len);
		src = dollar + 1;
		add_env_value(&str, &src, env);
		dollar = ft_strchr(src, '$');
	}
	str.data[str.len] = '\0';
	return (str.data);
}


char	*create_str(t_token *tokens)
{
	char	*str;

	str = malloc(tokens->len + 1);
	ft_memcpy(str, tokens->data, tokens->len + 1);
	return (str);
}
// char	**create_com_array(t_token **tokens, t_list **env)
// {
// 	char	**array;
// 	size_t	size;

// 	size = 0;
// 	while ((*tokens) && (*tokens)->type > TEXT)
// 	{
// 		size++;
// 		*tokens = (*tokens)->prev;
// 	}
// 	array = malloc((size + 1) * sizeof(char *));
// 	if(!size || array)
// 		return(NULL);
// 	array[size] = NULL;
// 	while (size)
// 	{
// 		if((*tokens)->type == TEXT)
// 			array[--size] = create_str(*tokens);
// 		// else if((*tokens)->type == ENV)
// 		// 	array[--size] = create_env_str(*tokens, env);
// 		*tokens = (*tokens)->next;
// 	}
// 	return (array);

// }

char *type(int type) //delete
{
	if(type == EMPTY)
		return ft_strdup("EMPTY");
	else if(type == TEXT)
		return ft_strdup("TEXT");
	else if(type ==  RED_RIGHT)
		return ft_strdup("RED_RIGHT");
	else if(type ==  RED_DRIGHT)
		return ft_strdup("RED_DRIGHT");
	else if(type ==  RED_LEFT)
		return ft_strdup("RED_LEFT");
	else if(type == PIPE)
		return ft_strdup("PIPE");
	else if(type == SEMICOLON)
		return ft_strdup("SEMICOLON");
	else if(type == OR)
		return ft_strdup("OR");
	else if(type == AND)
		return ft_strdup("AND");
	else if(type == ENV)
		return ft_strdup("ENV");
	else
		return ft_strdup("ERROR TYPE");
}

void	print_tokens(t_token *lst)
{
	printf("   TOKENS\n");
	while (lst)
	{
		printf("%-11s:  %s\n", type(lst->type), lst->data);
		lst = lst->prev;
	}
	printf("\n\n");
}
t_list	*create_com_lst(t_token **tokens, t_list **env)
{
	int			pipe_type;
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
	while(*tokens && ((*tokens)->type != SEMICOLON))
	{
		temp = *tokens;
		rsize = 0;
		//print_tokens(tokens);
		while (temp && temp->type != SEMICOLON && temp->type != PIPE)
		{
			if (temp->type <= RED_DRIGHT)
				rsize++;
			temp = temp->prev;
		}
		//printf("RED SIZE = %d\n", rsize);
		if (rsize)
		{
			red = malloc(sizeof(t_redir) * (rsize + 1));
			temp = *tokens;
			size = 0;
			while (temp && temp->type != SEMICOLON && temp->type != PIPE)
			{
				if(temp->type >= TEXT)
					size++;
				temp = temp->prev;
			}
			size -= rsize;
			printf("COM SIZE = %d\n", size);
			com_array = malloc(sizeof(char *) * (size + 1));
			com_array[size] = NULL;
			i = 0;
			j = 0;
			while (*tokens && (*tokens)->type != SEMICOLON && (*tokens)->type != PIPE)
			{
				if ((*tokens)->type <= RED_DRIGHT)
				{
					*tokens = (*tokens)->prev;
					red[i++] = red_create((*tokens)->data, (*tokens)->next->type);
				}
				else if (*tokens && (*tokens)->type == TEXT)
				{
					com_array[j++] = ft_strdup((*tokens)->data);
				}
				*tokens = (*tokens)->prev;

			}
			red[i] = red_create_last();

			if (pipe_type & PIPE_OUT)
					pipe_type |= PIPE_IN;
			if (*tokens && (*tokens)->type == PIPE)
				pipe_type |= PIPE_OUT;
			else
				pipe_type &= ~PIPE_OUT;

			// printf("\nCOMMANDS ARRAY\n");
			// for (size_t k = 0; com_array[k]; k++) // delete !!!
			// 	printf("%s\n", com_array[k]);

			cmd = com_create(com_array, red, pipe_type);
			node = ft_lstnew(cmd);
			ft_lstadd_back(&list_to_return, node);
		}
		else
		{
			temp = *tokens;
			size = 0;
			while (temp && temp->type != SEMICOLON && temp->type != PIPE)
			{
				if(temp->type >= TEXT)
					size++;
				temp = temp->prev;
			}
			// printf("COM SIZE = %d\n", size);
			com_array = malloc(sizeof(char *) * (size + 1));
			com_array[size] = NULL;
			i = 0;
			while (*tokens && (*tokens)->type != SEMICOLON && (*tokens)->type != PIPE)
			{
				if ((*tokens)->type == TEXT)
					com_array[i++] = ft_strdup((*tokens)->data); //create_str(*tokens);
				else if ((*tokens)->type == ENV)
					com_array[i++] = create_env_str((*tokens)->data, env);
				*tokens = (*tokens)->prev;
			}
			if (pipe_type & PIPE_OUT)
					pipe_type |= PIPE_IN;
			if (*tokens && (*tokens)->type == PIPE)
				pipe_type |= PIPE_OUT;
			else
				pipe_type &= ~PIPE_OUT;

			// printf("COMMANDS ARRAY\n");
			// for (size_t k = 0; com_array[k]; k++) // delete !!!
			// 	printf("%zu|%s|\n", k, com_array[k]);

			cmd = com_create(com_array, NULL, pipe_type);
			node = ft_lstnew(cmd);
			ft_lstadd_back(&list_to_return, node);
		}
	}
	if(*tokens && ((*tokens)->type == SEMICOLON))
				*tokens = (*tokens)->prev;
	return (list_to_return);
}

void pritn_com(void *com)
{
	t_command *cmd;
	int		i;

	cmd = com;
	i = 0;
	while ((cmd->com)[i])
	{
		printf("cmd = |%s|\n",(cmd->com)[i]);
		i++;
	}

}

void	tokens_handler(t_token **tokens, t_list **env)
{
	t_list		*commands;
	t_token		*end;

	commands = *env;

	end = *tokens;
	while (*tokens)
	{
		commands = create_com_lst(tokens, env);
		if(commands)
			commands_handler(commands, env);
		// if (*tokens && (*tokens)->prev)
		// {
		// 	*tokens = (*tokens)->prev;
		// 	clear_next(&((*tokens)->next), free);// del by next!!!!
		// }
		//ft_lstiter(commands, pritn_com);
		if (commands)
			ft_lstclear(&commands, com_clear);
	}
	clear_prev(&end, free);
	 //del by next!!!!
}

