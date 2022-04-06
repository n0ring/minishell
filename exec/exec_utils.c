/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 14:38:56 by namina             #+#    #+#            */
/*   Updated: 2021/08/14 14:38:56 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_child_fd(t_list *params)
{
	t_list_params	*element;

	element = (t_list_params *) params->content;
	if (element->file_fd[0] > 0)
		dup2(element->file_fd[0], STDIN_FILENO);
	if (element->file_fd[1] > 0)
		dup2(element->file_fd[1], STDOUT_FILENO);
	if (element->file_fd[1] == PIPE_FD)
		dup2(element->pipe_fd[1], STDOUT_FILENO);
	close(element->pipe_fd[1]);
	if (!((t_list_params *)params->content)->builtin)
		close(element->pipe_fd[0]);
}

void	parent_process_handler(t_list *params)
{
	t_list_params	*element;
	t_list			*tmp;
	int				status;

	tmp = params;
	while (tmp)
	{
		element = (t_list_params *) tmp->content;
		if (element->pid != -1 && element->pid != -2)
		{
			if (element->pipe_fd[0] != -1)
				close(element->pipe_fd[0]);
			waitpid(element->pid, &status, 0);
			if (WIFEXITED(status))
				g_last_exit_code = WEXITSTATUS(status);
		}
		if (element->builtin && element->pipe_fd[0] != -1)
		{
			close(element->pipe_fd[0]);
			element->pipe_fd[0] = -1;
		}
		if (element->pid == -1)
			g_last_exit_code = 1;
		tmp = tmp->next;
	}
}

int	builtin_exec(t_list *params, t_mshell *shell)
{
	int				stdout_copy;
	int				stdin_copy;
	t_list_params	*element;

	element = (t_list_params *) params->content;
	if (pipe(element->pipe_fd) == -1)
		return (pipe_error_handler());
	stdout_copy = dup(STDOUT_FILENO);
	if (stdout_copy == -1)
		return (pipe_error_handler());
	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1)
		return (pipe_error_handler());
	set_child_fd(params);
	element->builtin(shell, element);
	if (element->file_fd[0] > 0)
	{
		close(element->file_fd[0]);
		element->file_fd[0] = -1;
	}
	dup2(stdout_copy, STDOUT_FILENO);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdout_copy);
	close(stdin_copy);
	return (element->pipe_fd[0]);
}

void	get_input_from_std(char *limiter, int fd)
{
	char	*line;

	line = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		else
			break ;
		free(line);
		line = NULL;
	}
	free(line);
}

int	app_to_null(t_list_params *params, int check_pipe)
{
	if (check_pipe == PIPE_FD)
		ft_putstr_fd("syntax error: multiline pipe\n", 2);
	if (params->path_app)
		free(params->path_app);
	g_last_exit_code = 1;
	params->path_app = NULL;
	params->builtin = NULL;
	return (-1);
}
