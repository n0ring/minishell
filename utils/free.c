/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 21:06:31 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/08 21:06:31 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(void *node)
{
	t_envvar	*content;

	content = (t_envvar *)(node);
	free(content->key);
	free(content->value);
	free(content);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_io_params(void *param_node)
{
	t_list_io_params	*content;

	content = (t_list_io_params *)param_node;
	if (content->file_name)
		free(content->file_name);
	if (content->fd != -1 && content->fd != -2)
		close(content->fd);
	free(param_node);
}

void	free_params_lst(void *param_node)
{
	t_list_params	*content;

	content = (t_list_params *)param_node;
	if (content->cmd_arr)
		free_arr(content->cmd_arr);
	if (content->str_to_cmd)
		free(content->str_to_cmd);
	if (content->path_app)
		free(content->path_app);
	if (content->input)
		ft_lstclear(&content->input, free_io_params);
	if (content->output)
		ft_lstclear(&content->output, free_io_params);
	free(content);
}
