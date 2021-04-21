#include "../minibash.h"

static void upd_path(t_seq *tmp_seq, char *comm)
{
	char *tmp;

	tmp = tmp_seq->run;
	tmp_seq->run = ft_strdup(comm);
	free(tmp);
	tmp = tmp_seq->args[0];
	tmp_seq->args[0] = ft_strdup(comm);
	free(tmp);
}

static void concat_path(t_seq *tmp_seq, t_shell *shell, char **split, char *tmp)
{
	struct stat	s;
	size_t		i;
	char		*comm;

	i = 0;
	while (split[i])
	{
		tmp = ft_strjoin(split[i], "/");
		if (!tmp)
			free_split(&split, shell);
		comm = ft_strjoin(tmp, tmp_seq->args[0]);
		free(tmp);
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

static void full_or_wrong(t_seq *tmp_seq, t_shell *shell)
{
	char *tmp;

	tmp = tmp_seq->run;
	tmp_seq->run = ft_strdup(shell->seq->args[0]);
	free(tmp);
	if (!tmp_seq->run)
		free_error(strerror(errno), &shell);
}

static void find_path(t_seq *tmp_seq, t_shell *shell)
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

static int check_redirect(t_seq *tmp_seq, t_shell *shell)
{
	if (ft_strempty(tmp_seq->run))
	{
		free(tmp_seq->run);
		tmp_seq->run = NULL;
		return (1);
	}
	if ((tmp_seq->info & REDIR_OUT) && ft_strempty(tmp_seq->output))
		return (syntax_error(shell, '>'));
	if ((tmp_seq->info & REDIR_IN) && ft_strempty(tmp_seq->input))
		return (syntax_error(shell, '<'));
	return (0);
}

void	parse_one(t_seq *tmp_seq, t_shell *shell)
{
	struct stat	s;

	if ((tmp_seq->run && ft_strchrset(tmp_seq->run, "><")) || \
		ft_strchrset(shell->hist_curr->command, "><"))
	{
		parse_redirect(tmp_seq, shell);
		if (check_redirect(tmp_seq, shell))
			return;
	}
	if (!tmp_seq->run)
		tmp_seq->args = ft_split(shell->hist_curr->command, ' ');
	else
		tmp_seq->args = ft_split(tmp_seq->run, ' ');
	if (!tmp_seq->args)
		free_error(strerror(errno), &shell);
	if (is_builtin(tmp_seq->args[0]) || !stat(tmp_seq->args[0], &s) || \
		!envp_get_value(shell, "PATH"))
		full_or_wrong(tmp_seq, shell);
	else
		find_path(tmp_seq, shell);
}