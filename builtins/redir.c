/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:59:43 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 09:09:16 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

// flag = 1 : open and close
// flag = 0 : only open
// flag = 2 : only close
int	redir(t_seq *tmp_seq, char **str_low, int flag)
{
	static int	fds[2];
	int			res;

	res = 0;
	if (flag != 2)
	{
		fds[0] = dup(0);
		fds[1] = dup(1);
		res = run_redirect(tmp_seq);
	}
	if (flag || res)
	{
		dup2(fds[1], 1);
		dup2(fds[0], 0);
	}
	free(*str_low);
	*str_low = NULL;
	return (res);
}
