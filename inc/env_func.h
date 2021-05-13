/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:00:21 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/13 18:42:32 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_FUNC_H
# define ENV_FUNC_H

int		env_name_check(char *str);
int		env_len(char **env);
char	**env_dup(char **env);
char	*env_getname(char *str);
char	*env_getvalue(char *str);

#endif
