#include "../minibash.h"

static void shut_escape(t_seq *tmp_seq, t_quo *quo)
{
	// if (ft_strchr("|;", *quo->end) && (tmp_seq->info & QUOTED))
	// 	quo->last_slash = 0;
	if (!(quo->slashes % 2))
		quo->last_slash = 0;
	else
		quo->last_slash = 1;
	quo->slashes = quo->slashes / 2;
}

void join_args2(t_seq *tmp_seq, t_shell *shell, t_quo *quo, char **arg)
{
	char *tmp;

	tmp = *arg;
	if (quo->slashes)
	{
		shut_escape(tmp_seq, quo);
		*arg = ft_strjoin(*arg, ft_genstr('\\', quo->slashes));
	}
	else
		*arg = ft_strjoin(*arg, ft_substr(\
		tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start));
	free(tmp);
	if (!*arg)
		error_quotes(&quo, &shell);
}

static void join_args1(t_seq *tmp_seq, t_shell *shell, t_quo *quo, char **arg)
{
	// if (!quo->after_space && !tmp_split->arg)
	if (!*arg)
	{
		if (quo->slashes)
		{
			shut_escape(tmp_seq, quo);
			*arg = ft_genstr('\\', quo->slashes);
		}
		else
			*arg = ft_substr(\
			tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start);
		if (!*arg)
			error_quotes(&quo, &shell);
		quo->split_len++;
	}
	else
		join_args2(tmp_seq, shell, quo, arg);
}

void join_args(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	if (quo->after_space && tmp_split->arg)
	{
		if (init_quo_split(&tmp_split->next))
			error_quotes(&quo, &shell);
		if (quo->slashes)
		{
			shut_escape(tmp_seq, quo);
			tmp_split->next->arg = ft_genstr('\\', quo->slashes);
		}
		else
			tmp_split->next->arg = ft_substr(\
			tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start);
		if (!tmp_split->next->arg)
			error_quotes(&quo, &shell);
		quo->split_len++;
		quo->after_space = 0;
	}
	else
		join_args1(tmp_seq, shell, quo, &tmp_split->arg);
}

void join_one_sym(t_shell *shell, t_quo *quo, char **str, char *sym)
{
	char *tmp;

	tmp = *str;
	*str = ft_strjoin(*str, sym);
	free(tmp);
	if (!*str)
		error_quotes(&quo, &shell);
	quo->last_slash = 0;
	quo->end++;
}

void join_routine(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	if ((quo->start != quo->end) || \
	(quo->start == quo->end && (*quo->end == '\'' || *quo->end == '"')))
	{
		if (tmp_split)
			join_args(tmp_seq, shell, quo, tmp_split);
		else
		{
			if (!tmp_seq->tmp_redir->path)
			{
				tmp_seq->tmp_redir->path = ft_strdup("");
				if (!tmp_seq->tmp_redir->path)
					error_quotes(&quo, &shell);
			}
			join_args2(tmp_seq, shell, quo, &tmp_seq->tmp_redir->path);
		}
		quo->start = quo->end;
	}
}