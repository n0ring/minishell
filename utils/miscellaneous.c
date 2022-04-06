/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:22:04 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/23 18:22:04 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(char *prog)
{
	print_error(prog, NULL);
	exit(errno);
}

int	invalid_key(char *key)
{
	if (ft_isdigit(*key))
		return (1);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (1);
		key++;
	}
	return (0);
}

size_t	chr_arr_len(char **arr)
{
	size_t	res;

	res = 0;
	while (*arr)
	{
		res++;
		arr++;
	}
	return (res);
}

char	*crop(char *path)
{
	char	**path_elts;
	char	*res;
	char	*temp;
	size_t	i;

	path_elts = ft_split(path, '/');
	res = path;
	i = 1;
	if (chr_arr_len(path_elts) > 2)
	{
		res = path_elts[0];
		while (i < chr_arr_len(path_elts) - 1)
		{
			temp = ft_strjoin(res, "/");
			res = ft_strdup(temp);
			free(temp);
			temp = ft_strjoin(res, path_elts[i]);
			res = ft_strdup(temp);
			free(temp);
			i++;
		}
	}
	free_arr(path_elts);
	return (res);
}

void	init_el(t_list_params *el)
{
	el->path_app = NULL;
	el->cmd_arr = NULL;
	el->input = NULL;
	el->output = NULL;
	el->builtin = NULL;
	el->file_fd[0] = -1;
	el->file_fd[1] = -1;
	el->pid = -2;
	el->pipe_fd[0] = -1;
	el->pipe_fd[1] = -1;
}
