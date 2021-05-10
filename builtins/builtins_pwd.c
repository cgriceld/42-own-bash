/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:02:33 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/10 18:25:46 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

char	*pwd(t_shell *shell, t_seq *tmp_seq)
{
	char		*buf;
	size_t		size;

	buf = NULL;
	size = 0;
	buf = getcwd(buf, size);
	envp_set_value(shell, "PWD", buf);
	return (buf);
}

int	builtins_pwd(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	char	*buf;
	int		fds[2];

	fds[0] = dup(0);
	fds[1] = dup(1);
	run_redirect(tmp_seq, shell);
	free(str_low);
	buf = pwd(shell, tmp_seq);
	if (!buf)
		return (2);
	printf("%s", buf);
	free(buf);
	printf("\n");
	dup2(fds[1], 1);
	return (0);
}
