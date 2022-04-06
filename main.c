/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:55:17 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/01 18:55:17 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code = 0;

int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_mshell	shell;
	char		*untrimmed;

	(void)argv;
	init_shell(&shell, env);
	while (1)
	{
		handle_sigs(argc);
		untrimmed = readline(PROMPT);
		str = ft_strtrim(untrimmed, " \t");
		if (str && *str)
		{
			add_history(str);
			execution(str, &shell);
		}
		if (!str)
		{
			exit_routine(&shell);
			exit(g_last_exit_code);
		}
		free(untrimmed);
		free(str);
	}
	return (0);
}
