/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:28:17 by aalannys          #+#    #+#             */
/*   Updated: 2021/10/12 16:31:13 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h> //delete!

static unsigned long long	str_to_num(const char *start)
{
	unsigned long long	res;
	unsigned long long	rank;
	size_t				i;

	res = 0;
	rank = 1;
	i = 0;
	while (ft_isdigit(start[i]))
		i++;
	while (ft_isdigit(*start))
	{
		res += (*start - '0') * rank;
		rank *= 10;
		start--;
	}
	return (res);
}

int	ft_atoi(const char *nptr)
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
	return ((int)(res * is_minus));
}
