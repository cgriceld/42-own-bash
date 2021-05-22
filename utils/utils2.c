/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:00:52 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 14:00:53 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

char	*ft_strchrset(char *s, char *set)
{
	char	*tmp;

	tmp = s;
	while (*s && !ft_strchr(set, *s))
		s++;
	if (!*s)
		return (NULL);
	else
		return (s);
}

int	ft_strempty(char *s)
{
	while (*s == ' ')
		s++;
	if (*s == '\0')
		return (1);
	return (0);
}

int	ft_in_set(const char *set, char ch)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

char	*ft_low_str(char *str)
{
	char	*low_str;
	int		len;
	int		i;
	char	ch;

	len = ft_strlen(str);
	low_str = (char *)malloc(len + 1);
	if (!low_str)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		ch = str[i];
		if (ch >= 'A' && ch <= 'Z')
			ch = (char)((int)ch + 32);
		low_str[i] = ch;
		i++;
	}
	return (low_str);
}
