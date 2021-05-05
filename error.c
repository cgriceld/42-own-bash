#include "minibash.h"

void		lite_error(char *comment)
{
	printf("\n%s\n", comment);
	exit(EXIT_FAILURE);
}

static void	free_hist_env(t_shell **shell)
{
	t_history	*tmph;
	t_env		*tmpe;

	while ((*shell)->history)
	{
		tmph = (*shell)->history;
		(*shell)->history = (*shell)->history->next;
		if (tmph->command)
			free(tmph->command);
		if (tmph->cache)
			free(tmph->cache);
		free(tmph);
	}
	while ((*shell)->env)
	{
		tmpe = (*shell)->env;
		(*shell)->env = (*shell)->env->next;
		if (tmpe->key)
			free(tmpe->key);
		if (tmpe->value)
			free(tmpe->value);
		free(tmpe);
	}
}

static void free_redirect(t_redir_chain **redir)
{
	t_redir_chain *tmp;

	while (*redir)
	{
		tmp = *redir;
		*redir = (*redir)->next;
		if (tmp->path)
			free(tmp->path);
		free(tmp);
	}
}

void		free_seq(t_seq **seq)
{
	t_seq *tmp;

	while (*seq)
	{
		tmp = *seq;
		*seq = (*seq)->next;
		if (tmp->run)
			free(tmp->run);
		if (tmp->args)
			ft_twodarr_free(&tmp->args, ft_twodarr_len(tmp->args));
		if (tmp->redirect)
			free_redirect(&tmp->redirect);
		if (tmp->pipe)
			free_seq(&tmp->pipe);
		free(tmp);
	}
}

void		free_error(char *comment, t_shell **shell)
{
	if ((*shell)->history || (*shell)->env)
		free_hist_env(shell);
	if ((*shell)->seq)
		free_seq(&(*shell)->seq);
	free(*shell);
	if (comment)
		lite_error(comment);
}