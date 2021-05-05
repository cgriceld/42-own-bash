#include "../minibash.h"

static int quo_syntax_return(unsigned char flag)
{
	if (flag & DOUBLED)
		return (1);
	if (flag & SINGLE)
		return (2);
	return (0);
}

int even_escaped(char *start, char *str)
{
	int res;

	res = 0;
	str--;
	while (str != start && *str == '\\')
	{
		res++;
		str--;
	}
	if (!(res % 2))
		return (1);
	else
		return (0);
}

static void manage_quotes(char *str, unsigned char *flag, t_shell *shell)
{
	if (*str == '"')
	{
		if ((*flag & DOUBLED) && !(*flag & SINGLE) && even_escaped(shell->hist_curr->command, str))
			*flag &= ~DOUBLED;
		else if (!(*flag & SINGLE) && !(*flag & DOUBLED) && \
				even_escaped(shell->hist_curr->command, str))
			*flag |= DOUBLED;
	}
	else if (*str == '\'')
	{
		if ((*flag & SINGLE) && !(*flag & DOUBLED))
			*flag &= ~SINGLE;
		else if (!(*flag & SINGLE) && !(*flag & DOUBLED) && \
				even_escaped(shell->hist_curr->command, str))
			*flag |= SINGLE;
	}
}

static void manage_separator(t_shell *shell, char **start, char *str, char sym)
{
	char *tmp;

	tmp = shell->seq->run;
	shell->seq->run = ft_strjoin_sym(\
	ft_substr(shell->hist_curr->command, *start - shell->hist_curr->command, \
			str - *start), str, sym);
	free(tmp);
	if (!shell->seq->run)
		free_error(strerror(errno), &shell);
	*start = str + 1;
	if (sym == ' ' && *str == ';')
		shell->sep[0]++;
	if (sym == ' ' && *str == '|')
		shell->sep[1]++;
}

// check for start string bound when slash
static int quo_syntax(char *str, unsigned char flag, t_shell *shell, char *start)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			manage_quotes(str, &flag, shell);
		else if (*str == ';' || *str == '|')
		{
			if (*str == '|' && !(flag & DOUBLED) && !(flag & SINGLE) && *(str - 1) == '>')
			{
				if (!even_escaped(shell->hist_curr->command, str))
					shell->sep[1]++;
			}
			else if (!(flag & DOUBLED) && !(flag & SINGLE) && *(str - 1) == '\\')
			{
				if (even_escaped(shell->hist_curr->command, str))
					manage_separator(shell, &start, str, ' ');
			}
			else if ((flag & SINGLE) || (flag & DOUBLED))
				manage_separator(shell, &start, str, '\\');
			else
			{
				if (*str == ';')
					shell->sep[0]++;
				else if (*str == '|')
					shell->sep[1]++;
			}
		}
		str++;
	}
	return (quo_syntax_return(flag));
}

int precheck_syntax(t_shell *shell)
{
	int res;
	unsigned char flag;
	char *start;

	if (ft_strchrset(shell->hist_curr->command, "'\";|"))
	{
		shell->seq->info |= QUOTED;
		shell->sep[0] = 0;
		shell->sep[1] = 0;
		flag = ZERO;
		start = shell->hist_curr->command;
		res = quo_syntax(shell->hist_curr->command, flag, shell, start);
		if (!res)
			return (0);
		if (res == 1)
			syntax_error(shell, '"');
		else if (res == 2)
			syntax_error(shell, '\'');
		free_seq(&shell->seq);
		return (1);
	}
	return (0);
}