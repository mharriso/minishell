/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:00:21 by tjuliean          #+#    #+#             */
/*   Updated: 2021/06/06 14:37:17 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_FUNC_H
# define ENV_FUNC_H

# include "libft.h"

int		env_name_check(char *str);
char	*env_getname(char *str);
char	*env_getvalue(char *str);
int		env_replace(const char *name, const char *value, t_list **env);
t_list	*env_create(char **env);
void	env_clear(void *v);
char	*e_name(t_list *env);
char	*e_value(t_list *env);
char	**env_listtoarr(t_list *env);
char	*env_getvaluebyname(const char *name, t_list *env);
char	**env_listtoarr_to_new(t_list *env);
char	*str_env(const char *name, const char *value);

#endif
