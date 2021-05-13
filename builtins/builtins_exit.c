/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:00:08 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/12 22:27:25 by lesia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../Downloads/42-own-bash-main/minibash.h"

int	static	too_many_args(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	write(1, "exit: too many arguments\n", 25);
	ret_status = 2;
	redir(shell, tmp_seq, str_low, 2);
	return (ret_status);
}

int	static	two_args(t_shell *shell, t_seq *tmp_seq, char *copy, char *str_low)
{
	write(1, "exit: ", 6);
	write(1, tmp_seq->args[1], ft_strlen(tmp_seq->args[1]));
	write(1, ": numeric argument required\n", 28);
	ret_status = 2;
	free(copy);
	redir(shell, tmp_seq, str_low,2);
	return (ret_status);
}

// flag = 1 : open and close
// flag = 0 : only open
// flag = 2 : only close
int	redir(t_shell *shell, t_seq *tmp_seq, char *str_low, int flag)
{
	static int fds[2];
	int res;

	res = 0;
	if (flag != 2)
	{
		fds[0] = dup(0);
		fds[1] = dup(1);
		res = run_redirect(tmp_seq, shell);
	}
	if (flag || res)
	{
		dup2(fds[1], 1);
		dup2(fds[0], 0);
	}
	//free(str_low);
	return (res);
}

int	builtins_exit(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	int		n_args;
	long long int		num;
	char	*copy;

	if (redir(shell, tmp_seq, str_low, 1))
		return (2);
	ret_status = 0;
	n_args = 0;
	write(2, "exit\n", 5);
	while (tmp_seq->args[n_args] != 0)
		n_args++;
	if (n_args > 1)
	{
		num = ft_atoi(tmp_seq->args[1]);
		copy = ft_itoa(num);
		if (ft_strncmp(tmp_seq->args[1], copy, ft_strlen(tmp_seq->args[1])))
			return (two_args(shell, tmp_seq, copy, str_low));
		if (num < 0)
			ret_status = num % 256 + 256;
		else if (num > 0)
			ret_status = 256 + num % 256;
		free(copy);
	}
	if ((n_args) > 2)
		return (too_many_args(shell, tmp_seq,  str_low));
	redir(shell, tmp_seq, str_low, 2);
	free_error(NULL, &shell);
	exit(ret_status);
}
