#include "../minibash.h"

static void	upd_path(t_seq *tmp_seq, char *comm)
{
	char *tmp;

	tmp = tmp_seq->run;
	tmp_seq->run = ft_strdup(comm);
	free(tmp);
}

static void	concat_path(t_seq *tmp_seq, t_shell *shell, char **split, char *t)
{
	struct stat	s;
	size_t		i;
	char		*comm;

	i = 0;
	while (split[i])
	{
		t = ft_strjoin(split[i], "/");
		if (!t)
			free_split(&split, shell);
		comm = ft_strjoin(t, tmp_seq->args[0]);
		free(t);
		if (!comm)
			free_split(&split, shell);
		if (!stat(comm, &s))
		{
			upd_path(tmp_seq, comm);
			free(comm);
			if (!tmp_seq->run || !tmp_seq->args[0])
				free_split(&split, shell);
			return;
		}
		free(comm);
		i++;
	}
}

static void	full_or_wrong(t_seq *tmp_seq, t_shell *shell)
{
	char *tmp;

	tmp = tmp_seq->run;
	tmp_seq->run = ft_strdup(tmp_seq->args[0]);
	free(tmp);
	if (!tmp_seq->run)
		free_error(strerror(errno), &shell);
}

static void	find_path(t_seq *tmp_seq, t_shell *shell)
{
	char		**split;
	char		*tmp;

	tmp = envp_get_value(shell, "PATH");
	split = ft_split(tmp, ':');
	if (!split)
		free_error(strerror(errno), &shell);
	concat_path(tmp_seq, shell, split, tmp);
	ft_twodarr_free(&split, ft_twodarr_len(split));
	if (!tmp_seq->run)
		full_or_wrong(tmp_seq, shell);
}

void	parse_one(t_seq *tmp_seq, t_shell *shell)
{
	struct stat	s;

	if ((tmp_seq->run && ft_strchrset(tmp_seq->run, "$<>'\"\\")) || \
		(!tmp_seq->run && ft_strchrset(shell->hist_curr->command, "$<>'\"\\")))
	{
		parse_quotes(tmp_seq, shell);
		if (!tmp_seq->run || (shell->seq->info & SYNTAX_ERR))
			return;
	}
	else
	{
		if (!tmp_seq->run)
			tmp_seq->args = ft_split(shell->hist_curr->command, ' ');
		else
			tmp_seq->args = ft_split(tmp_seq->run, ' ');
		if (!tmp_seq->args)
			free_error(strerror(errno), &shell);
	}
	if (is_builtin(tmp_seq->args[0]) || !envp_get_value(shell, "PATH") || \
		ft_strchr(tmp_seq->args[0], '/'))
		full_or_wrong(tmp_seq, shell);
	else
		find_path(tmp_seq, shell);
}
