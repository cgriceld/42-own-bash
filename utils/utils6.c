/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:01:38 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 14:01:39 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static int	ft_nlen(int n)
{
	int	i;

	if (n <= 0)
		i = 1;
	else
		i = 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	ft_itoa_utils(int *len, int *sign, int n)
{
	*len = ft_nlen(n);
	if (n < 0)
		*sign = -1;
	else
		*sign = 1;
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	ft_itoa_utils(&len, &sign, n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str += len;
	*str-- = '\0';
	if (!n)
		*str = '0';
	while (n)
	{
		*str = sign * (n % 10) + 48;
		if (n > 9 || n < -9)
			str--;
		n /= 10;
	}
	if (sign < 0)
		*--str = '-';
	return (str);
}
