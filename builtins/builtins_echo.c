/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:59:43 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/16 16:06:09 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	builtins_echo(t_seq *tmp_seq, char *str_low)
{
	int		n;
	int		i;

	if (redir(tmp_seq, &str_low, 0))
		return (2);
	g_ret_status = 0;
	n = 0;
	if (tmp_seq->args[1] != NULL)
	{
		while (tmp_seq->args[n + 1] != NULL &&
		ft_strncmp(tmp_seq->args[n + 1], "-n", 3) == 0)
			n += 1;
		i = 1;
		while (tmp_seq->args[i + n] != NULL && tmp_seq->args[i + n + 1] != NULL)
		{
			write(1, tmp_seq->args[i + n], ft_strlen(tmp_seq->args[i + n]));
			write(1, " ", 1);
			i++;
		}
		if (tmp_seq->args[i + n] != NULL)
		{
			write(1, tmp_seq->args[i + n], ft_strlen(tmp_seq->args[i + n]));
		}
		if (n == 0)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	redir(tmp_seq, &str_low, 2);
	return (g_ret_status);
}
