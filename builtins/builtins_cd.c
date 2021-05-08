/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 22:39:21 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/05 11:15:16 by lesia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

//больште буквы

char	*find_path(t_shell *shell, char *path, char *match)
{
	path = envp_get_value(shell, match);
	if (!path)
	{
		printf("cd: %s not set\n", match);
		ret_status = 2;
		return (NULL);
	}
	return (path);
}

void	update_pwd(t_shell *shell, char *path, char *old_path, t_seq *tmp_seq)
{
	if (is_oldpwd == 0)
	{
		if (envp_get_value(shell, "OLDPWD") == NULL)
			envp_new_value(shell, ft_strdup("OLDPWD"), NULL);
		is_oldpwd = 1;
	}
	free(path);
	path = pwd(shell, tmp_seq);
	if (ft_strncmp(old_path, path, ft_strlen(old_path + 1)) != 0)
	{
		envp_set_value(shell, "OLDPWD", old_path);
		envp_set_value(shell, "PWD", path);
	}
	else
	{
		free(old_path);
		free(path);
	}
}

int		builtins_cd(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	char *path;
	char *old_path;
	char *param;

	free(str_low);
	ret_status = 0;
	param = ft_strtrim(tmp_seq->args[1], "\n");
	old_path = pwd(shell, tmp_seq);
	if (!old_path)
		return (2);
	if (!param || (ft_strncmp(param, "", 1) == 0))
		path = find_path(shell, path, "HOME");
	else if (ft_strncmp(param, "-", 2) == 0)
		path = find_path(shell, path, "OLDPWD");
	else
		path = param;
	if (param && ret_status == 0 && chdir(path) != 0)
	{
		printf("cd: %s: No such file or directory\n", param);
		ret_status = 2;
	}
	if (param)
		free(param);
	if (ret_status == 0)
		update_pwd(shell, path, old_path, tmp_seq);
	return (ret_status);
}
