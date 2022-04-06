/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:06:44 by aalannys           #+#    #+#            */
/*   Updated: 2021/09/05 12:06:44 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctl_c_handle(int x)
{
	(void)x;
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_exit_code = 1;
}

void	handle_sigs(int argc)
{
	(void)argc;
	rl_catch_signals = 0;
	signal(SIGINT, ctl_c_handle);
	signal(SIGQUIT, SIG_IGN);
}

void	print_nl(int x)
{
	g_last_exit_code = 128 + x;
	write(1, "\n", 1);
}

void	handle_for_child(char *path_app)
{
	if (path_app)
	{
		if (!ft_strncmp("./minishell", path_app, ft_strlen(path_app)))
			signal(SIGINT, SIG_IGN);
		else
		{
			signal(SIGINT, print_nl);
			signal(SIGQUIT, print_nl);
		}
	}
}
