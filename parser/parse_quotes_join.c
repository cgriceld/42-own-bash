#include "../minibash.h"

static void check_others2(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	char *tmp;

	if (!quo->after_space)
	{
		tmp = tmp_split->arg;
		if (quo->slashes)
		{
			if (quo->slashes == 1 && quo->last_slash)
				quo->slashes = 0;
			tmp_split->arg = ft_strjoin(tmp_split->arg, ft_genstr('\\', quo->slashes));
		}
		else
			tmp_split->arg = ft_strjoin(tmp_split->arg, ft_strtrim(ft_substr(\
			tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start), "'\""));
		free(tmp);
		if (!tmp_split->arg)
			error_quotes(&quo, &shell);
	}
}

static void check_others(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	// if (!quo->after_space && !tmp_split->arg)
	if (!tmp_split->arg)
	{
		if (quo->slashes)
		{
			if (quo->slashes == 1 && quo->last_slash)
				quo->slashes = 0;
			tmp_split->arg = ft_genstr('\\', quo->slashes);
		}
		else
			tmp_split->arg = ft_strtrim(ft_substr(\
			tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start), "'\"");
		if (!tmp_split->arg)
			error_quotes(&quo, &shell);
		quo->split_len++;
	}
	else
		check_others2(tmp_seq, shell, quo, tmp_split);
}

void join_args(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	if (quo->after_space && tmp_split->arg)
	{
		if (init_quo_split(&tmp_split->next))
			error_quotes(&quo, &shell);
		if (quo->slashes)
		{
			if (quo->slashes == 1 && quo->last_slash)
				quo->slashes = 0;
			tmp_split->next->arg = ft_genstr('\\', quo->slashes);
		}
		else
			tmp_split->next->arg = ft_strtrim(ft_substr(\
			tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start), "'\"");
		if (!tmp_split->next->arg)
			error_quotes(&quo, &shell);
		quo->split_len++;
		quo->after_space = 0;
	}
	else
		check_others(tmp_seq, shell, quo, tmp_split);
}

void join_one_sym(t_shell *shell, t_quo *quo, t_quo_split *tmp_split, char *sym)
{
	char *tmp;

	tmp = tmp_split->arg;
	tmp_split->arg = ft_strjoin(tmp_split->arg, sym);
	free(tmp);
	if (!tmp_split->arg)
		error_quotes(&quo, &shell);
	quo->last_slash = 0;
	quo->end++;
}

void join_routine(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	if (quo->start != quo->end)
	{
		join_args(tmp_seq, shell, quo, tmp_split);
		//quo->after_space = 0;
		quo->start = quo->end;
	}
}