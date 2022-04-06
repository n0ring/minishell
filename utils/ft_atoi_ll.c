/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ll.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:37:08 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/23 18:37:08 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned long long	str_to_num(const char *start)
{
	unsigned long long	res;
	unsigned long long	rank;

	res = 0;
	rank = 1;
	while (ft_isdigit(*start))
		start++;
	start--;
	while (ft_isdigit(*start))
	{
		res += (*start - '0') * rank;
		rank *= 10;
		start--;
	}
	return (res);
}

long long	ft_atoi_ll(const char *nptr)
{
	int					is_minus;
	unsigned long long	res;

	if (!(*nptr))
		return (0);
	is_minus = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			is_minus = -1;
		nptr++;
	}
	res = str_to_num(nptr);
	return ((long long)(res * is_minus));
}
