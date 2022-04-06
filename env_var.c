/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:44:39 by aalannys           #+#    #+#            */
/*   Updated: 2021/09/05 18:44:39 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_mshell *shell, char *env[])
{
	t_envvar	*var;
	t_list		*node;
	int			i;
	char		**str_var;

	i = 0;
	str_var = NULL;
	while (env[i])
	{
		var = malloc(sizeof(t_envvar));
		if (!var)
			error_exit(NULL);
		str_var = ft_split(env[i], '=');
		if (!str_var)
			error_exit(NULL);
		var->key = ft_strdup(str_var[0]);
		var->value = ft_strdup(str_var[1]);
		var->display_flag = 1;
		node = ft_lstnew(var);
		if (!node)
			error_exit(NULL);
		ft_lstadd_back(&shell->env_copy, node);
		free_arr(str_var);
		i++;
	}
}

t_list	*get_by_key(t_mshell *shell, char *key)
{
	t_list	*temp;
	char	*curr_key;

	temp = shell->env_copy;
	while (temp)
	{
		curr_key = ((t_envvar *)(temp->content))->key;
		if (!ft_strncmp(curr_key, key, ft_strlen(curr_key))
			&& !ft_strncmp(curr_key, key, ft_strlen(key)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	set_by_key(t_mshell *shell, char *key, char *val)
{
	t_list		*temp;
	char		*curr_key;
	t_envvar	*curr_var;

	temp = shell->env_copy;
	while (temp)
	{
		curr_var = (t_envvar *)(temp->content);
		curr_key = curr_var->key;
		if (!ft_strncmp(curr_key, key, ft_strlen(curr_key))
			&& !ft_strncmp(curr_key, key, ft_strlen(key)))
		{
			if (curr_var->value)
				free(curr_var->value);
			curr_var->value = NULL;
			curr_var->value = ft_strdup(val);
			curr_var->display_flag = 1;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

char	**lst_to_arr(t_mshell *shell)
{
	int			i;
	char		**envp;
	t_list		*temp;
	char		*str_tmp;

	envp = malloc(sizeof(char *) * (ft_lstsize(shell->env_copy) + 1));
	if (!envp)
		error_exit(NULL);
	temp = shell->env_copy;
	i = 0;
	while (temp)
	{
		if (((t_envvar *)(temp->content))->display_flag)
		{
			str_tmp = ft_strjoin(((t_envvar *)(temp->content))->key, "=");
			envp[i] = ft_strjoin(str_tmp, ((t_envvar *)(temp->content))->value);
			free(str_tmp);
			i++;
		}
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	add_var(t_mshell *shell, char *key, char *val, int display)
{
	t_list		*last_node;
	t_list		*node_before_last;
	t_list		*new_node;
	t_envvar	*new_var;

	last_node = get_by_key(shell, "_");
	node_before_last = shell->env_copy;
	while (node_before_last->next != last_node)
		node_before_last = node_before_last->next;
	new_var = malloc(sizeof(t_envvar));
	if (!new_var)
		error_exit(NULL);
	if (val)
		*new_var = (t_envvar){.key = ft_strdup(key), .value = ft_strdup(val),
			.display_flag = display};
	else
		*new_var = (t_envvar){.key = ft_strdup(key), .value = NULL,
			.display_flag = display};
	new_node = ft_lstnew(new_var);
	node_before_last->next = new_node;
	new_node->next = last_node;
}
