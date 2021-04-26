#include "../minibash.h"

int is_ignored(char *start, char *ptr, t_shell *shell)
{
	unsigned char flag;
	char *tmp;

	flag = ZERO;
	tmp = ptr;
	if (ptr != start)
	{
		ptr--;
		if (*ptr == '\\')
			flag |= ESCAPED;
	}
	while (ptr != start)
	{
		if (*ptr == '\'' || *ptr == '"')
		{
			flag |= SINGLE;
			break;
		}
		ptr--;
	}
	if (((flag & ESCAPED) && !(flag & SINGLE)) || (flag & SINGLE))
		return (1);
	return (0);
}

static int quo_syntax_return(unsigned char flag)
{
	if (flag & DOUBLED)
		return (1);
	if (flag & SINGLE)
		return (2);
	return (0);
}

static int quo_syntax(char *str)
{
	unsigned char flag;

	flag = ZERO;
	while (*str)
	{
		if (*str == '"')
		{
			if (*(str - 1) == '\\' && !(flag & SINGLE) && (flag & DOUBLED))
			{
				str++;
				continue;
			}
			if (!(flag & SINGLE) && (flag & DOUBLED))
				flag &= ~DOUBLED;
			else if (!(flag & SINGLE))
				flag |= DOUBLED;
		}
		else if (*str == '\'')
		{
			if (!(flag & DOUBLED) && (flag & SINGLE))
				flag &= ~SINGLE;
			else if (!(flag & DOUBLED))
				flag |= SINGLE;
		}
		str++;
	}
	return (quo_syntax_return(flag));
}

int precheck_quotes(t_shell *shell)
{
	int token;

	if (ft_strchrset(shell->hist_curr->command, "'\""))
	{
		shell->seq->info |= QUOTED;
		token = quo_syntax(shell->hist_curr->command);
		if (!token)
			return (0);
		if (token == 1)
			syntax_error(shell, '"');
		else if (token == 2)
			syntax_error(shell, '\'');
		free_seq(&shell->seq);
		return (1);
	}
	return (0);
}