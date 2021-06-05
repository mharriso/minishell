/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 13:10:09 by tjuliean          #+#    #+#             */
/*   Updated: 2021/06/05 17:13:21 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define RED_LEFT 1
# define RED_RIGHT 2
# define RED_DRIGHT 3

# define PIPE_IN 1
# define PIPE_OUT 2

# include <unistd.h>

typedef struct s_fdi
{
	int		fd[2];
	int		type;
}				t_fdi;

typedef struct s_fork
{
	pid_t	pid;
	t_fdi	fd[2];
	int		pipe_type;
}				t_fork;

typedef struct s_redir
{
	char	*fname;
	int		type;
	int		fd;
}				t_redir;

typedef struct s_command
{
	char	**com;
	t_redir	*red;
	t_fork	*info;
	int		pipe_type;
}				t_command;

typedef struct s_env
{
	char	*name;
	char	*value;
}				t_env;

#endif
