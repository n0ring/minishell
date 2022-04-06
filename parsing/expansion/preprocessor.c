/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                      :+:      :+:   :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:47:41 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/10 15:47:41 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 1. check if all quotes are closed
 2. in case they are not paired, throw parse error, clear cmds, reload prompt
 3. set 2 flags: 1 - inside double quotes, 2 - inside single quotes
 4. if one type of quotes is inside another - don't remove the ones that are
 inside, remove only the ones that are outside
 5. if you are inside double quotes, set a flag and try to expand everything
 that starts with $, except for this case: $'. In this case leave the $ sign
 as it is
 6. if you are inside single quotes, just leave everything as it is
 7. if you meet n-spaces and none of the flags are set, that means that the
 part of the string up to this moment is a separate cmd_array element. All
 spaces (ft_isspace) are skipped
 */

void	move_spaces(char **str, char **start)
{
	while (ft_isspace(**str))
		(*str)++;
	*start = *str;
}

char	*add_elt(char **start, char **str, char *res)
{
	size_t	dst;
	char	*tmp;
	char	*added;

	dst = *str - *start;
	tmp = ft_substr(*start, 0, dst + 1);
	added = ft_strjoin(res, tmp);
	free(tmp);
	if (*res)
		free(res);
	*start += dst;
	move_spaces(str, start);
	return (added);
}

char	*add_rest(char *start, char *str, char *res)
{
	size_t	dst;
	char	*tmp;
	char	*new_res;

	dst = str - start;
	if (dst == 0)
		return (res);
	tmp = ft_substr(start, 0, dst);
	new_res = ft_strjoin(res, tmp);
	if (*res)
		free(res);
	free(tmp);
	return (new_res);
}

void	update_qstatus(char curr, t_quotes *quotes)
{
	if (curr == '\'' && !(quotes->doubl % 2))
		quotes->singl++;
	if (curr == '\"' && !(quotes->singl % 2))
		quotes->doubl++;
}

char	*preprocessor(char *str, t_mshell *shell)
{
	t_quotes	q;
	char		*res;
	char		*start;

	q = (t_quotes){.doubl = 0, .singl = 0};
	res = "";
	start = str;
	move_spaces(&str, &start);
	while (*str)
	{
		update_qstatus(*str, &q);
		if (ft_isspace(*str) && !(q.doubl % 2) && !(q.singl % 2))
		{
			res = add_elt(&start, &str, res);
			continue ;
		}
		if (*str == '$' && !(q.singl % 2))
		{
			res = add_expanded(&start, &str, res, shell);
			continue ;
		}
		str++;
	}
	res = add_rest(start, str, res);
	return (res);
}
