#include "../minibash.h"

static void error_dollar(char **value, t_quo *quo, t_shell *shell)
{
	free(*value);
	error_quotes(&quo, &shell);
}

static void exp_dollar2(char **value, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	char *tmp;

	if (!quo->after_space)
	{
		tmp = tmp_split->arg;
		tmp_split->arg = ft_strjoin(tmp_split->arg, ft_strdup(*value));
		free(tmp);
		if (!tmp_split->arg)
			error_dollar(value, quo, shell);
	}
}

static void exp_dollar(char **value, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	char *tmp;

	if (quo->after_space && tmp_split->arg)
	{
		if (init_quo_split(&tmp_split->next))
			error_dollar(value, quo, shell);
		tmp_split->next->arg = ft_strdup(*value);
		if (!tmp_split->next->arg)
			error_dollar(value, quo, shell);
		quo->split_len++;
		quo->after_space = 0;
	}
	else if (!tmp_split->arg)
	{
		tmp_split->arg = ft_strdup(*value);
		if (!tmp_split->next->arg)
			error_dollar(value, quo, shell);
		quo->split_len++;
	}
	else
		exp_dollar2(value, shell, quo, tmp_split);
}

static int prepare_dollar(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	quo->end++;
	if (*quo->end == ' ' || !*quo->end)
	{
		quo->start--;
		join_args(tmp_seq, shell, quo, tmp_split);
		return (1);
	}
	else if (ft_isdigit(*quo->end))
		quo->start = ++quo->end;
	while (*quo->end && *quo->end != ' ' && *quo->end != '$')
		quo->end++;
	return (0);
}

void parse_dollar(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	char *exp;
	char *value;

	quo->start++;
	if (prepare_dollar(tmp_seq, shell, quo, tmp_split))
		return;
	exp = ft_substr(tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start);
	if (!exp)
		error_quotes(&quo, &shell);
	value = envp_get_value(shell, exp);
	if (!value && !ft_isdigit(*(quo->start - 1)))
	{
		free(exp);
		return;
	}
	if (!value)
		value = exp;
	exp_dollar(&value, shell, quo, tmp_split);
	free(value);
}