/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:00:21 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/16 14:33:27 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_FUNC_H
# define ENV_FUNC_H

#include "structs.h"
#include "libft.h"

int		env_name_check(char *str);
int		env_len(char **env);
char	**env_dup(char **env);
char	*env_getname(char *str);
char	*env_getvalue(char *str);
int		env_replace(const char *str, char ***env);
int		env_index_byname(const char *name, const char **env);
t_list	*env_create(char **env);
void	env_clear(void *v);

#endif
