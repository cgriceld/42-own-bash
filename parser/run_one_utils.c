/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_one_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:56:10 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 13:56:15 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	run_builtin(t_seq *tmp_seq, t_shell *shell)
{
	char	*tmp;

	tmp = ft_low_str(tmp_seq->run);
	if (!ft_strncmp(tmp, "echo", ft_strlen(tmp_seq->run)))
		return (builtins_echo(tmp_seq, tmp, 0, 0));
	else if (!ft_strncmp(tmp_seq->run, "cd", ft_strlen(tmp_seq->run)))
		return (builtins_cd(shell, tmp_seq, tmp, NULL));
	else if (!ft_strncmp(tmp, "pwd", ft_strlen(tmp_seq->run)))
		return (builtins_pwd(shell, tmp_seq, tmp));
	else if (!ft_strncmp(tmp, "env", ft_strlen(tmp_seq->run)))
		return (builtins_env(shell, tmp_seq, tmp));
	else if (!ft_strncmp(tmp_seq->run, "unset", ft_strlen(tmp_seq->run)))
		return (builtins_unset_value(shell, tmp_seq, tmp, 0));
	else if (!ft_strncmp(tmp_seq->run, "export", ft_strlen(tmp_seq->run)))
		return (builtins_export(shell, tmp_seq, tmp, 0));
	else if (!ft_strncmp(tmp_seq->run, "exit", ft_strlen(tmp_seq->run)))
		return (builtins_exit(shell, tmp_seq, tmp, 0));
	return (0);
}

void	handle_eacces(char *comm)
{
	struct stat	s;

	if (!ft_strchr(comm, '/'))
	{
		write(2, ": command not found\n", 20);
		exit(127);
	}
	if (!stat(comm, &s) && S_ISDIR(s.st_mode))
		write(2, ": is a directory\n", 17);
	else
		write(2, ": Permission denied\n", 20);
	exit(126);
}
