/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 22:39:21 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/22 10:55:41 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

char	*find_path(t_shell *shell, char *path, char *match)
{
	path = envp_get_value(shell, match);
	if (!path)
	{
		write(2, "cd: ", 4);
		write(2, match, ft_strlen(match));
		write(2, ": not set\n", 10);
		g_ret_status = 1;
		return (NULL);
	}
	return (path);
}

void	update_pwd(t_shell *shell, char *path, char *old_path)
{
	path = pwd(shell);
	if (envp_get_value(shell, "OLDPWD") == NULL)
		envp_new_value(shell, ft_strdup("OLDPWD"), NULL);
	if (ft_strncmp(old_path, path, ft_strlen(old_path + 1)) != 0)
	{
		envp_set_value(shell, "OLDPWD", old_path);
		envp_set_value(shell, "PWD", path);
	}
	free(old_path);
	free(path);
}

void	static	local_print(char *param, char *path, int local)
{
	if (local == 1)
	{
		write(2, "cd: ", 4);
		write(2, param, ft_strlen(param));
		write(2, ": No such file or directory\n", 28);
		g_ret_status = 1;
	}
	else
	{
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
}

int	builtins_cd(t_shell *shell, t_seq *tmp_seq, char *str_low, char	*param)
{
	char	*path;
	char	*old_path;

	if (redir(tmp_seq, &str_low, 1))
		return (1);
	g_ret_status = 0;
	param = tmp_seq->args[1];
	old_path = pwd(shell);
	if (!old_path)
		return (1);
	path = NULL;
	if (!param || (ft_strncmp(param, "", 1) == 0))
		path = find_path(shell, path, "HOME");
	else if (ft_strncmp(param, "-", 2) == 0)
	{
		path = find_path(shell, path, "OLDPWD");
		local_print(param, path, 0);
	}
	else
		path = param;
	if (path && g_ret_status == 0 && chdir(path) != 0)
		local_print(param, path, 1);
	if (g_ret_status == 0)
		update_pwd(shell, path, old_path);
	return (g_ret_status);
}
