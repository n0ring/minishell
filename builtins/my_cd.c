/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:15:34 by aalannys           #+#    #+#            */
/*   Updated: 2021/09/08 14:15:34 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_dr(t_mshell *shell, char *path)
{
	chdir(path);
	set_by_key(shell, "PWD", path);
}

int	try_upper_dir(char *curr_path, t_mshell *shell)
{
	t_list	*old_pwd;

	if (!ft_strncmp(curr_path, "..", 2))
	{
		old_pwd = get_by_key(shell, "OLDPWD");
		if (old_pwd)
			change_dr(shell, ((t_envvar *)(old_pwd->content))->value);
		else
		{
			old_pwd = get_by_key(shell, "PWD");
			if (old_pwd)
				change_dr(shell, crop(((t_envvar *)(old_pwd->content))->value));
		}
		return (1);
	}
	else if (!ft_strncmp(curr_path, ".", ft_strlen(curr_path)))
	{
		print_error("cd", "error retrieving current directory: "
			"getcwd: cannot access parent directories");
		return (1);
	}
	return (0);
}

int	check_pwds(t_mshell *shell, char *path)
{
	t_list	*pwd;
	t_list	*old_pwd;
	char	*curr_path;

	curr_path = NULL;
	curr_path = getcwd(curr_path, 1);
	if (!curr_path)
	{
		if (try_upper_dir(path, shell))
			return (1);
		print_error("cd", NULL);
		return (1);
	}
	pwd = get_by_key(shell, "PWD");
	if (!pwd)
		add_var(shell, "PWD", curr_path, 1);
	old_pwd = get_by_key(shell, "OLDPWD");
	if (!old_pwd)
		add_var(shell, "OLDPWD", ft_strdup(curr_path), 1);
	free(curr_path);
	return (0);
}

int	use_chdir(t_mshell *shell, char **cmd_arr)
{
	t_list	*elt;
	int		res;

	elt = get_by_key(shell, "HOME");
	if (!cmd_arr[1] && !elt)
	{
		print_err_msg("cd", NULL, "HOME not set");
		return (-1);
	}
	if (cmd_arr[1])
		res = chdir(cmd_arr[1]);
	else
		res = chdir(((t_envvar *)(elt->content))->value);
	if (res == -1)
	{
		print_error("cd", cmd_arr[1]);
	}
	return (res);
}

void	my_cd(t_mshell *shell, struct s_list_params *params)
{
	int		res;
	char	*curr_path;
	t_list	*pwd;

	if (check_pwds(shell, params->cmd_arr[1]))
		return ;
	res = use_chdir(shell, params->cmd_arr);
	if (res == -1)
		return ;
	curr_path = NULL;
	curr_path = getcwd(curr_path, 1);
	if (!curr_path)
	{
		printf("in my_cd\n");
		print_error("cd", NULL);
		return ;
	}
	pwd = get_by_key(shell, "PWD");
	set_by_key(shell, "OLDPWD", ((t_envvar *)(pwd->content))->value);
	set_by_key(shell, "PWD", curr_path);
	free(curr_path);
	g_last_exit_code = 0;
}
