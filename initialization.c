/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                     :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:26:36 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/24 18:26:36 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_func(t_list_params *param)
{
	size_t	len;

	len = ft_strlen(param->cmd_arr[0]);
	if (!ft_strncmp(param->cmd_arr[0], "echo", len))
		param->builtin = my_echo;
	else if (!ft_strncmp(param->cmd_arr[0], "env", len))
		param->builtin = my_env;
	else if (!ft_strncmp(param->cmd_arr[0], "pwd", len))
		param->builtin = my_pwd;
	else if (!ft_strncmp(param->cmd_arr[0], "cd", len))
		param->builtin = my_cd;
	else if (!ft_strncmp(param->cmd_arr[0], "export", len))
		param->builtin = my_export;
	else if (!ft_strncmp(param->cmd_arr[0], "unset", len))
		param->builtin = my_unset;
	else if (!ft_strncmp(param->cmd_arr[0], "exit", len))
		param->builtin = my_exit;
	else
		param->builtin = NULL;
}

void	init_shell(t_mshell *shell, char **env)
{
	t_list		*elt;
	t_envvar	*var;
	int			val;

	*shell = (t_mshell){.env_copy = NULL};
	parse_env(shell, env);
	elt = get_by_key(shell, "SHLVL");
	if (!elt)
		add_var(shell, "SHLVL", "1", 1);
	else
	{
		var = (t_envvar *)(elt->content);
		if (var->value && *var->value)
		{
			val = ft_atoi(var->value);
			free(var->value);
			var->value = ft_itoa(val + 1);
		}
		else
			set_by_key(shell, "SHLVL", "1");
	}
}
