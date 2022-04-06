/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:10:19 by namina             #+#    #+#            */
/*   Updated: 2021/08/12 19:10:19 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork_manager(t_list_params *element)
{
	if (element->path_app && element->path_app[0])
		element->pid = fork();
	if (element->pid == -1)
	{
		perror("Minishell: fork");
		return (-1);
	}
	return (0);
}

void	close_pipes_parent(void *params)
{
	t_list_params	*element;

	element = (t_list_params *) params;
	if (element->pipe_fd[0] != -1)
	{
		close(element->pipe_fd[0]);
		element->pipe_fd[0] = -1;
	}
}

int	pipe_error_handler(void)
{
	print_error(NULL, NULL);
	return (-1);
}

void	child_here_doc(t_list_io_params *io_el, int fds[])
{
	signal(SIGINT, SIG_DFL);
	close(fds[0]);
	get_input_from_std(io_el->file_name, fds[1]);
	close(fds[1]);
	exit(SUCCESS);
}

int	here_doc(t_list_io_params *io_el)
{
	int	pid;
	int	status;
	int	fds[2];

	pipe(fds);
	pid = fork();
	if (pid == 0)
		child_here_doc(io_el, fds);
	handle_for_child(" ");
	close(fds[1]);
	wait(&status);
	io_el->fd = fds[0];
	if (WIFSIGNALED(status))
	{
		g_last_exit_code = 1;
		return (SUCCESS);
	}
	else
		g_last_exit_code = 0;
	return (0);
}
