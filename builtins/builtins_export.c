/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:39:09 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/10 20:09:38 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	pair_param_value(t_seq *tmp_seq, int i, char **param, char **value)
{
	int	n;
	int	len;

	*value = NULL;
	*param = NULL;
	len = ft_strlen(tmp_seq->args[i]);
	n = 0;
	while (tmp_seq->args[i][n] != '=' && len > 0)
	{
		n++;
		len--;
	}
	if (len > 0)
	{
		tmp_seq->args[i][n] = 0;
		*value = ft_strdup(&(tmp_seq->args[i][n + 1]));
	}
	*param = ft_strdup(tmp_seq->args[i]);
	//тут течет, надо понять где
}

int	check_is_valid(t_seq *tmp_seq, int i)
{
	int	n;

	n = 0;
	if ((tmp_seq->args[i][0] == '_') || (tmp_seq->args[i][0] >= 'a'
										 && tmp_seq->args[i][0] <= 'z') || (tmp_seq->args[i][0] >= 'A' && tmp_seq->args[i][0] <= 'Z'))
		n++;
	else
	{
		printf("export: `%s': not a valid identifier\n", tmp_seq->args[i]);
		return (2);
	}
	while (tmp_seq->args[i][n] != 0 && tmp_seq->args[i][n] != '=')
	{
		if ((tmp_seq->args[i][n] == '_') || (tmp_seq->args[i][n] == '\n')
			|| (tmp_seq->args[i][n] >= 'a' && tmp_seq->args[i][n] <= 'z')
			|| (tmp_seq->args[i][n] >= 'A' && tmp_seq->args[i][n] <= 'Z')
			|| (tmp_seq->args[i][n] >= '0' && tmp_seq->args[i][n] <= '9'))
			n++;
		else
		{
			printf("export: '%s': not a valid identifier\n", tmp_seq->args[i]);
			return (2);
		}
	}
	return (0);
}

int	builtins_export(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	char	*value;
	char	*param;
	int		i;

	redir(shell, tmp_seq, str_low);
	if (tmp_seq->args[1] == 0 || tmp_seq->args[1][0] == '\n')
		return (print_export(shell));
	i = 1;
	while (tmp_seq->args[i] != 0)
	{
		value = NULL;
		param = NULL;
		if (check_is_valid(tmp_seq, i) == 2)
			return (2);
		pair_param_value(tmp_seq, i, &param, &value);
		if (value == NULL && envp_get_value(shell, param) != NULL)
			i = i;
		else if (envp_set_value(shell, param, value) == 0)
			i = i;
		else
			envp_new_value(shell, param, value);
		i++;
	}
	return (0);
}