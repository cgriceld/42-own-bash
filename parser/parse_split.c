#include "../minibash.h"

int syntax_error(t_shell *shell, char sym)
{
	printf("-minibash: syntax error near unexpected token `%c'\n", sym);
	shell->seq->info |= SYNTAX_ERR;
	ret_status = 258;
	return (1);
}

static int fill_lst(t_seq *tmp_seq, t_shell *shell, char **split, char sym)
{
	size_t	i;
	char *tmp;

	i = 0;
	while (split[i])
	{
		tmp = tmp_seq->run;
		tmp_seq->run = ft_strtrim(split[i], " ");
		free(tmp);
		if (!tmp_seq->run)
			return (1);
		if (!*tmp_seq->run)
		{
			syntax_error(shell, sym);
			break;
		}
		if (split[i + 1] && init_seq(&tmp_seq->next))
			return (1);
		if (sym == '|' && split[i + 1])
			tmp_seq->info |= PIPE;
		tmp_seq = tmp_seq->next;
		i++;
	}
	return (0);
}

static int check_separator(t_shell *shell, char sym, size_t len, char *str)
{
	if (sym == '|')
	{
		if ((shell->seq->info & QUOTED) && shell->sep[1] + 1 != len)
			return (syntax_error(shell, sym));
		else if (!(shell->seq->info & QUOTED) && ft_numchstr(str, sym) + 1 != len)
			return (syntax_error(shell, sym));
	}
	else if (sym == ';')
	{
		if ((shell->seq->info & QUOTED) && shell->sep[0] > len)
			return (syntax_error(shell, sym));
		else if (!(shell->seq->info & QUOTED) && ft_numchstr(str, sym) > len)
			return (syntax_error(shell, sym));
	}
	return (0);
}

void parse_split(t_seq *tmp_seq, t_shell *shell, char sym, char *str)
{
	char **split;

	if (sym == ';' && str[0] == sym)
	{
		syntax_error(shell, sym);
		return;
	}
	split = ft_split(str, sym);
	if (!split)
		free_error(strerror(errno), &shell);
	if (check_separator(shell, sym, ft_twodarr_len(split), str))
	{
		ft_twodarr_free(&split, ft_twodarr_len(split));
		return;
	}
	if (fill_lst(tmp_seq, shell, split, sym))
		free_split(&split, shell);
	ft_twodarr_free(&split, ft_twodarr_len(split));
	if (shell->seq->info & SYNTAX_ERR)
		return;
	while (tmp_seq)
	{
		if (ft_strchr(tmp_seq->run, '|'))
		{
			if (init_seq(&tmp_seq->pipe))
				free_error(strerror(errno), &shell);
			else
				parse_split(tmp_seq->pipe, shell, '|', tmp_seq->run);
			if (shell->seq->info & SYNTAX_ERR)
				return;
			tmp_seq = tmp_seq->next;
			continue;
		}
		parse_one(tmp_seq, shell);
		if (shell->seq->info & SYNTAX_ERR)
			return;
		tmp_seq = tmp_seq->next;
	}
}