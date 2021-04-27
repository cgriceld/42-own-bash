#include "../minibash.h"

// int is_ignored(char *start, char *ptr, t_shell *shell)
// {
// 	unsigned char flag;
// 	char *tmp;

// 	flag = ZERO;
// 	tmp = ptr;
// 	if (ptr != start)
// 	{
// 		ptr--;
// 		if (*ptr == '\\')
// 			flag |= ESCAPED;
// 	}
// 	while (ptr != start)
// 	{
// 		if (*ptr == '\'' || *ptr == '"')
// 		{
// 			flag |= SINGLE;
// 			break;
// 		}
// 		ptr--;
// 	}
// 	if (((flag & ESCAPED) && !(flag & SINGLE)) || (flag & SINGLE))
// 		return (1);
// 	return (0);
// }

// static int quo_syntax(char *str, unsigned char flag)
// {
// 	while (*str)
// 	{
// 		if (*str == '"')
// 		{
// 			if ((*(str - 1) == '\\') && (*(str - 2) != '\\') && \
// 				!(flag & SINGLE) && (flag & DOUBLED))
// 			{
// 				str++;
// 				continue;
// 			}
// 			if (!(flag & SINGLE) && (flag & DOUBLED))
// 				flag &= ~DOUBLED;
// 			else if (!(flag & SINGLE))
// 				flag |= DOUBLED;
// 		}
// 		else if (*str == '\'')
// 		{
// 			if (!(flag & DOUBLED) && (flag & SINGLE))
// 				flag &= ~SINGLE;
// 			else if (!(flag & DOUBLED))
// 				flag |= SINGLE;
// 		}
// 		str++;
// 	}
// 	return (quo_syntax_return(flag));
// }

static int quo_syntax_return(unsigned char flag)
{
	if (flag & DOUBLED)
		return (1);
	if (flag & SINGLE)
		return (2);
	return (0);
}

static void manage_quotes(char *str, unsigned char *flag)
{
	if (*str == '"')
	{
		if ((*(str - 1) == '\\') && (*(str - 2) != '\\') && \
			!(*flag & SINGLE) && (*flag & DOUBLED))
			return;
		if (!(*flag & SINGLE) && (*flag & DOUBLED))
			*flag &= ~DOUBLED;
		else if (!(*flag & SINGLE))
			*flag |= DOUBLED;
	}
	else if (*str == '\'')
	{
		if (!(*flag & DOUBLED) && (*flag & SINGLE))
			*flag &= ~SINGLE;
		else if (!(*flag & DOUBLED))
			*flag |= SINGLE;
	}
}

static void manage_separator(t_shell *shell, char **start, char *str, char sym)
{
	char *tmp;

	tmp = shell->seq->run;
	shell->seq->run = ft_strjoin_sym(\
	ft_substr(shell->hist_curr->command, *start - shell->hist_curr->command, str - *start), str, sym);
	free(tmp);
	if (!shell->seq->run)
		free_error(strerror(errno), &shell);
	*start = str + 1;
	if (sym == ' ')
		shell->sep[0]++;
}

static int quo_syntax(char *str, unsigned char flag, t_shell *shell)
{
	char *start;

	start = shell->hist_curr->command;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			manage_quotes(str, &flag);
		else if (*str == ';' || *str == '|')
		{
			// if (!(flag & DOUBLED) && !(flag & SINGLE) && *(str - 1) == '\\' \
			// 	&& *(str - 2) != '\\')
			// {
			// 	str++;
			// 	continue;
			// }
			if (!(flag & DOUBLED) && !(flag & SINGLE) && *(str - 1) == '\\' \
				&& *(str - 2) == '\\')
				manage_separator(shell, &start, str, ' ');
			else if (((flag & SINGLE) && *(str - 1) != '\\') || \
				((flag & DOUBLED) && *(str - 1) != '\\'))
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

	if (ft_strchrset(shell->hist_curr->command, "'\"\\"))
	{
		shell->seq->info |= QUOTED;
		flag = ZERO;
		res = quo_syntax(shell->hist_curr->command, flag, shell);
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