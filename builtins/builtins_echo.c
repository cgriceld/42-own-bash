/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:59:43 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/03 18:08:15 by lesia            ###   ########.fr       */
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

int		builtins_echo(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	int		n;
	int		i;
	char	*tmp;

	free(str_low);
	ret_status= 0;
	n = 0;
	if (tmp_seq->args[1] != NULL)
	{
		if (ft_strncmp(ft_strtrim(tmp_seq->args[1], "\n"), "-n", 3) == 0)
			n = 1;
		i = 1;
		while (tmp_seq->args[i + n - 1] != NULL)
		{
			print_echo(tmp_seq, i, n);
//			tmp = ft_strtrim(tmp_seq->args[i + n - 1], "\n");
//			printf("%s ", tmp);
//			free(tmp);
			i++;
		}
		if (tmp_seq->args[i + n] != NULL)
		{
			print_echo(tmp_seq, i, n);
//			tmp = ft_strtrim(tmp_seq->args[i + n], "\n");
//			printf("%s", tmp);
//			free(tmp);
		}
		if (n == 0)
			printf("\n");
	}
	return (ret_status);
}
