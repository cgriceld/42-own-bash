/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:02:33 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/12 12:33:18 by cgriceld         ###   ########.fr       */
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

	if (redir(shell, tmp_seq, str_low, 0))
		return (2);
	str_low = NULL;
	buf = pwd(shell, tmp_seq);
	if (!buf)
		return (2);
	printf("%s", buf);
	free(buf);
	printf("\n");
	redir(shell, tmp_seq, str_low, 2);
	return (0);
}
