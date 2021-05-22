/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:00:33 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 14:00:35 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static int	ft_issign(const char c)
{
	return (c == 43 || c == 45);
}

static int	ft_isspace(const char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	long long int	prevn;
	long long int	n;
	int				sign;

	n = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (ft_issign(*str) && *str++ == '-')
		sign = -1;
	while (*str && ft_isdigit(*str))
	{
		prevn = n;
		n = 10 * n + sign * (*str++ - 48);
		if (n > prevn && sign == -1)
			return (0);
		if (n < prevn && sign == 1)
			return (-1);
	}
	return (n);
}
