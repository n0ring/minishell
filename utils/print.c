/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:42:41 by aalannys            #+#   #+#            */
/*   Updated: 2021/09/07 15:42:41 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *prog, char *arg)
{
	if (!prog && !arg)
		perror("Minishell");
	else
	{
		write(2, "Minishell: ", 11);
		if (prog && arg)
		{
			ft_putstr_fd(prog, 2);
			ft_putstr_fd(": ", 2);
			perror(arg);
		}
		if (!arg)
			perror(prog);
		if (!prog)
			perror(arg);
	}
	g_last_exit_code = 1;
}

void	print_node(void *node)
{
	t_envvar	*var;

	var = (t_envvar *)node;
	if (var->display_flag)
	{
		printf("%s=", var->key);
		if (var->value)
			printf("%s", var->value);
		printf("\n");
	}
}

void	print_export(void *node)
{
	t_envvar	*var;

	var = (t_envvar *)node;
	printf("declare -x ");
	if (var->display_flag)
	{
		printf("%s=", var->key);
		if (var->value)
			printf("\"%s\"", var->value);
		printf("\n");
	}
	else
		printf("%s\n", var->key);
}

void	print_err_msg(char *prog, char *arg, char *msg)
{
	ft_putstr_fd("Minishell: ", 2);
	if (prog)
	{
		ft_putstr_fd(prog, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	g_last_exit_code = 1;
}
