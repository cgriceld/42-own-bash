/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_join_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:52:20 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 13:52:23 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	shut_escape(t_quo *quo)
{
	if (!(quo->slashes % 2))
		quo->last_slash = 0;
	else
		quo->last_slash = 1;
	quo->slashes = quo->slashes / 2;
}

void	join_args2_utils(t_quo *quo, char **tmp2, char **arg)
{
	if (quo->slashes == -1)
	{
		*tmp2 = ft_itoa(g_ret_status);
		*arg = ft_strjoin(*arg, *tmp2);
		free(*tmp2);
	}
}
