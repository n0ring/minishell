/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:26:58 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/07 16:26:58 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_env(t_mshell *shell, struct s_list_params *params)
{
	(void)params;
	ft_lstiter(shell->env_copy, print_node);
	g_last_exit_code = 0;
}

void	my_pwd(t_mshell *shell, struct s_list_params *params)
{
	t_list	*node;
	char	*curr_dir;

	(void)params;
	curr_dir = NULL;
	node = get_by_key(shell, "PWD");
	if (!node || !((t_envvar *)(node->content))->value
		|| !(((t_envvar *)(node->content))->value[0]))
	{
		curr_dir = getcwd(curr_dir, 1);
		if (!curr_dir)
		{
			print_error("pwd", NULL);
			return ;
		}
		printf("%s\n", curr_dir);
	}
	else
		printf("%s\n", ((t_envvar *)(node->content))->value);
	g_last_exit_code = 0;
}

void	my_echo(t_mshell *shell, struct s_list_params *params)
{
	char	*param;
	size_t	i;
	int		new_line;

	(void)shell;
	i = 1;
	param = params->cmd_arr[i];
	new_line = 1;
	while (params->cmd_arr[i] && !ft_strncmp("-n", param,
			ft_strlen(param)) && ft_strlen(param) > 0)
	{
		new_line = 0;
		param = params->cmd_arr[++i];
	}
	while (i < chr_arr_len(params->cmd_arr) - 1)
		printf("%s ", params->cmd_arr[i++]);
	if (params->cmd_arr[i])
		printf("%s", params->cmd_arr[i]);
	if (new_line)
		printf("\n");
	g_last_exit_code = 0;
}
