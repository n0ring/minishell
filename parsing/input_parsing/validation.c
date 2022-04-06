/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c     		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 19:10:54 by namina             #+#    #+#            */
/*   Updated: 2021/09/10 19:10:54 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_path(char *cmd_name)
{
	while (*cmd_name == '.')
		cmd_name++;
	if (*cmd_name == '/')
		return (1);
	return (0);
}

void	check_status_path(t_list *params)
{
	t_list_params	*param;

	param = (t_list_params *)(params->content);
	if (!param->path_app)
	{
		if (!(is_path(param->cmd_arr[0])))
		{
			print_err_msg(NULL, param->cmd_arr[0], "command not found");
			g_last_exit_code = 127;
		}
		free_arr(param->cmd_arr);
		param->cmd_arr = NULL;
	}
	else
	{
		if (access(param->path_app, X_OK))
		{
			print_err_msg(NULL, param->path_app, "permission denied");
			free(param->path_app);
			param->path_app = NULL;
			g_last_exit_code = 126;
		}
	}
}

void	assign_path(t_list_params *el, struct stat *buf)
{
	int	err;

	err = stat(el->cmd_arr[0], buf);
	if (err == -1)
	{
		print_error(NULL, el->cmd_arr[0]);
		return ;
	}
	el->path_app = ft_strdup(el->cmd_arr[0]);
}

void	check_access(char **path, t_list_params *el)
{
	char			**path_pointer;
	struct stat		*buf;
	int				err;

	path_pointer = path;
	buf = malloc(sizeof(struct stat));
	if (is_path(el->cmd_arr[0]))
	{
		assign_path(el, buf);
		free_arr(path);
		free(buf);
		return ;
	}
	while (path && *path_pointer)
	{
		err = stat(*path_pointer, buf);
		if (err != -1)
		{
			el->path_app = ft_strdup(*path_pointer);
			break ;
		}
		path_pointer++;
	}
	free_arr(path);
	free(buf);
}

int	validation(t_list *param_list, char **envp)
{
	char			**path;
	t_list_params	*el;

	while (param_list)
	{
		el = (t_list_params *)param_list->content;
		if (!el->cmd_arr || !el->cmd_arr[0])
		{
			param_list = param_list->next;
			continue ;
		}
		assign_func(el);
		if (el->builtin)
		{
			param_list = param_list->next;
			continue ;
		}
		path = get_path_arr(envp, el->cmd_arr[0]);
		check_access(path, el);
		check_status_path(param_list);
		param_list = param_list->next;
	}
	return (0);
}
