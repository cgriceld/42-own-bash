/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:59:43 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/10 18:17:41 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	print_echo(t_seq *tmp_seq, int i, int n)
{
	char	*tmp;

	tmp = ft_strtrim(tmp_seq->args[i + n - 1], "\n");
	if (tmp[0] != 0)
		printf("%s ", tmp);
	free(tmp);
}

int	builtins_echo(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	int		n;
	int		i;
	int		fds[2];

	fds[0] = dup(0);
	fds[1] = dup(1);
	run_redirect(tmp_seq, shell);
	free(str_low);
	ret_status = 0;
	n = 0;
	if (tmp_seq->args[1] != NULL)
	{
		if (ft_strncmp(ft_strtrim(tmp_seq->args[1], "\n"), "-n", 3) == 0)
			n += 1;
		i = 0;
		while (tmp_seq->args[++i + n + 1] != NULL)
			printf("%s ", tmp_seq->args[i + n]);
		if (tmp_seq->args[i + n] != NULL)
			printf("%s", tmp_seq->args[i + n]);
		if (n == 0)
			printf("\n");
	}
	dup2(fds[1], 1);
	return (ret_status);
}
