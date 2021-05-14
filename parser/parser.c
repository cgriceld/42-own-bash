#include "../minibash.h"

void	free_split(char ***split, t_shell *shell)
{
	ft_twodarr_free(split, ft_twodarr_len(*split));
	free_error(strerror(errno), &shell);
}

int	init_seq(t_seq **seq)
{
	*seq = (t_seq *)malloc(sizeof(t_seq));
	if (!seq)
		return (1);
	(*seq)->run = NULL;
	(*seq)->args = NULL;
	(*seq)->pipe = NULL;
	(*seq)->redirect = NULL;
	(*seq)->tmp_redir = NULL;
	(*seq)->info = ZERO;
	(*seq)->next = NULL;
	return (0);
}

int			is_builtin(char *s)
{
	char *tmp;
	int len;

	tmp = ft_low_str(s);
	len = ft_strlen(s);
	if ((len == 4 && !ft_strncmp(tmp, "echo", len)) \
	|| (len == 2 && !ft_strncmp(tmp, "cd", len)) \
	|| (len == 3 && !ft_strncmp(tmp, "pwd", len)) \
	|| (len == 3 && !ft_strncmp(tmp, "env", len)) \
	|| (len == 5 && !ft_strncmp(s, "unset", len)) \
	|| (len == 6 && !ft_strncmp(s, "export", len)) \
	|| (len == 4 && !ft_strncmp(s, "exit", len)))
	{
		free(tmp);
		return (1);
	}
	else
	{
		free(tmp);
		return (0);
	}
}

static void run(t_seq *tmp_seq, t_shell *shell)
{
	while (tmp_seq)
	{
		if (tmp_seq->pipe || (tmp_seq->info & PIPE))
		{
			if (tmp_seq->pipe)
				ret_status = run_pipe(tmp_seq->pipe, shell);
			else
				ret_status = run_pipe(tmp_seq, shell);
			//printf("%d\n", ret_status);
			if (tmp_seq->info & PIPE)
				break;
			tmp_seq = tmp_seq->next;
			continue;
		}
		ret_status = run_one(tmp_seq, shell);
		//printf("%d\n", ret_status);
		tmp_seq = tmp_seq->next;
	}
}

void		parser(t_shell *shell)
{
	t_seq	*tmp_seq;

	if (init_seq(&shell->seq))
		free_error(strerror(errno), &shell);
	tmp_seq = shell->seq;
	if (precheck_syntax(shell))
		return;
	if (ft_strchr(shell->hist_curr->command, ';'))
	{
		if ((shell->seq->info & QUOTED) && tmp_seq->run)
			parse_split(tmp_seq, shell, ';', tmp_seq->run);
		else
			parse_split(tmp_seq, shell, ';', shell->hist_curr->command);
	}
	else if (ft_strchr(shell->hist_curr->command, '|'))
	{
		if ((shell->seq->info & QUOTED) && tmp_seq->run)
			parse_split(tmp_seq, shell, '|', tmp_seq->run);
		else
			parse_split(tmp_seq, shell, '|', shell->hist_curr->command);
	}
	else
		parse_one(tmp_seq, shell);
	if (!(shell->seq->info & SYNTAX_ERR))
		run(tmp_seq, shell);
	free_seq(&shell->seq);
}