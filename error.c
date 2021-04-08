#include "minibash.h"

void lite_error(char *comment)
{
	printf("\n%s\n", comment);
	exit(EXIT_FAILURE);
}

void free_shell(t_shell **shell)
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
		free(tmpe->key);
		free(tmpe->value);
		free(tmpe);
	}
	free(*shell);
}

void free_error(char *comment, t_shell **shell)
{
	free_shell(shell);
	lite_error(comment);
}