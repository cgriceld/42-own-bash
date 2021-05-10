/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:00:08 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/10 18:25:46 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	static	too_many_args(void)
{
	printf("exit: too many arguments");
	ret_status = 2;
	return (ret_status);
}

int	static	two_args(t_seq *tmp_seq, char *copy)
{
	printf("exit: %s: numeric argument required", tmp_seq->args[1]);
	ret_status = 2;
	free(copy);
	return (ret_status);
}

void	redir(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	int		fds[2];

	fds[0] = dup(0);
	fds[1] = dup(1);
	run_redirect(tmp_seq, shell);
	dup2(fds[1], 1);
	free(str_low);
}

int	builtins_exit(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	int		n_args;
	int		num;
	char	*copy;

	redir(shell, tmp_seq, str_low);
	ret_status = 0;
	n_args = 0;
	while (tmp_seq->args[n_args] != 0)
		n_args++;
	if (n_args > 1)
	{
		num = ft_atoi(tmp_seq->args[1]);
		copy = ft_itoa(num);
		if (ft_strncmp(tmp_seq->args[1], copy, ft_strlen(tmp_seq->args[1])))
			return (two_args(tmp_seq, copy));
		if (num < 0)
			ret_status = num % 256 + 256;
		else if (num > 0)
			ret_status = 256 + num % 256;
		free(copy);
	}
	if ((n_args) > 2)
		return (too_many_args());
	free_error(NULL, &shell);
	exit(ret_status);
}
