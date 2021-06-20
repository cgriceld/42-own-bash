#include "../minibash.h"

static int	exp_dollar2(char *value, char **str)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, value);
	free(tmp);
	if (!*str)
		return (1);
	return (0);
}

static int	exp_dollar(char *value, t_quo *quo, t_quo_split *tmp_split)
{
	if (quo->after_space && tmp_split->arg)
	{
		if (init_quo_split(&tmp_split->next))
			return (1);
		tmp_split->next->arg = ft_strdup(value);
		if (!tmp_split->next->arg)
			return (1);
		quo->split_len++;
		quo->after_space = 0;
	}
	else if (!tmp_split->arg)
	{
		tmp_split->arg = ft_strdup(value);
		if (!tmp_split->arg)
			return (1);
		quo->split_len++;
	}
	else
		return (exp_dollar2(value, &tmp_split->arg));
	return (0);
}

static int	prepare_dollar(t_seq *tmp_seq, t_shell *shell, t_quo *quo, \
						t_quo_split *tmp_split)
{
	quo->start++;
	quo->end++;
	if (!*quo->end || ft_strchr(" <>\\$=", *quo->end))
	{
		quo->start--;
		join_routine(tmp_seq, shell, quo, tmp_split);
		return (1);
	}
	if (*quo->end == '?')
	{
		quo->slashes = -1;
		join_routine(tmp_seq, shell, quo, tmp_split);
		quo->slashes = 0;
		quo->end++;
		return (1);
	}
	else if (ft_isdigit(*quo->end))
	{
		quo->end++;
		return (1);
	}
	while (*quo->end && !ft_strchr(" $<>\"\\'=", *quo->end))
		quo->end++;
	return (0);
}

static int	exp_dollar_utils(char *value, t_seq *tmp_seq)
{
	if (!tmp_seq->tmp_redir->path)
	{
		tmp_seq->tmp_redir->path = ft_strdup("");
		if (!tmp_seq->tmp_redir->path)
			return (1);
	}
	if (exp_dollar2(value, &tmp_seq->tmp_redir->path))
		return (1);
	return (0);
}

void	parse_dollar(t_seq *tmp_seq, t_shell *shell, t_quo *quo, \
					t_quo_split *tmp_split)
{
	char	*exp;
	char	*value;

	if (prepare_dollar(tmp_seq, shell, quo, tmp_split))
		return ;
	exp = ft_substr(tmp_seq->run, quo->start - tmp_seq->run, \
					quo->end - quo->start);
	if (!exp)
		error_quotes(&quo, &shell);
	value = envp_get_value(shell, exp);
	if (!value)
	{
		free(exp);
		return ;
	}
	if (tmp_split)
	{
		if (exp_dollar(value, quo, tmp_split))
			error_dollar(&exp, quo, shell);
	}
	else if (exp_dollar_utils(value, tmp_seq))
		error_dollar(&exp, quo, shell);
	free(exp);
}
