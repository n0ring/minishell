/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:25:44 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/13 15:25:44 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_str(char ***res, char **start, char *prep)
{
	char	**new_arr;
	char	*temp;
	size_t	i;

	temp = ft_substr(*start, 0, prep - *start);
	*start += ft_strlen(temp) + 1;
	if (!(*temp))
	{
		free(temp);
		return ;
	}
	new_arr = malloc(sizeof(char *) * (chr_arr_len(*res) + 2));
	if (!new_arr)
		error_exit(NULL);
	i = 0;
	while (i < chr_arr_len(*res))
	{
		new_arr[i] = (*res)[i];
		i++;
	}
	new_arr[i] = temp;
	new_arr[i + 1] = NULL;
	free(*res);
	*res = new_arr;
}

char	**split_args(char *prep)
{
	t_quotes	q;
	char		**res;
	char		*start;

	q = (t_quotes){.doubl = 0, .singl = 0};
	res = malloc(sizeof(char *));
	if (!res)
		error_exit(NULL);
	res[0] = NULL;
	start = prep;
	while (*prep)
	{
		if (*prep == '\'')
			q.singl++;
		if (*prep == '\"')
			q.doubl++;
		if (ft_isspace(*prep) && !(q.doubl % 2) && !(q.singl % 2))
			add_str(&res, &start, prep);
		prep++;
	}
	add_str(&res, &start, prep);
	return (res);
}

char	**parse_args(char *args, t_mshell *shell)
{
	char	*preprocessed;
	char	**res;
	int		i;

	if (check_quotes(args))
		return (NULL);
	preprocessed = preprocessor(args, shell);
	res = split_args(preprocessed);
	free(preprocessed);
	i = 0;
	while (res[i])
	{
		res[i] = remove_quotes(res[i]);
		i++;
	}
	return (res);
}
