/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:00:08 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/22 09:56:24 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	static	too_many_args(t_seq *tmp_seq, char *str_low)
{
	write(1, "exit: too many arguments\n", 25);
	g_ret_status = 1;
	redir(tmp_seq, &str_low, 2);
	return (g_ret_status);
}

int	static	not_num_arg(t_shell *shell, t_seq *tmp_seq, \
char *copy, char *str_low)
{
	write(1, "exit: ", 6);
	write(1, tmp_seq->args[1], ft_strlen(tmp_seq->args[1]));
	write(1, ": numeric argument required\n", 28);
	g_ret_status = 255;
	free(copy);
	redir(tmp_seq, &str_low, 2);
	free_error(NULL, &shell);
	exit(g_ret_status);
}

void	side_quest(long long int num, char *copy)
{
	if (num < 0)
		g_ret_status = num % 256 + 256;
	else if (num > 0)
		g_ret_status = 256 + num % 256;
	free(copy);
}

int	side_quest_0(t_seq *tmp_seq, int pluses)
{
	pluses = 0;
	if (tmp_seq->args[1][pluses] == '+')
		pluses++;
	return (pluses);
}

int	builtins_exit(t_shell *shell, t_seq *tmp_seq, char *str_low, int n_args)
{
	long long int		num;
	char				*copy;
	int					pluses;

	if (redir(tmp_seq, &str_low, 1))
		return (1);
	g_ret_status = 0;
	write(2, "exit\n", 5);
	while (tmp_seq->args[n_args] != 0)
		n_args++;
	if (n_args > 1)
	{
		pluses = side_quest_0(tmp_seq, 0);
		num = ft_atoi(&(tmp_seq->args[1][pluses]));
		copy = ft_itoa(num);
		if (ft_strncmp(&(tmp_seq->args[1][pluses]), copy, \
		ft_strlen(&(tmp_seq->args[1][pluses]))))
			return (not_num_arg(shell, tmp_seq, copy, str_low));
		side_quest (num, copy);
	}
	if ((n_args) > 2)
		return (too_many_args(tmp_seq, str_low));
	redir(tmp_seq, &str_low, 2);
	free_error(NULL, &shell);
	exit(g_ret_status);
}
