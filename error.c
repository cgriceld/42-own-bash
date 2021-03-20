#include "minibash.h"

void lite_error(char *comment)
{
	printf("\n%s\n", comment);
	exit(EXIT_FAILURE);
}

void free_shell(t_shell **shell)
{
	t_history *tmp;

	if ((*shell)->history)
	{
		while ((*shell)->history)
		{
			tmp = (*shell)->history;
			(*shell)->history = (*shell)->history->next;
			if (tmp->command)
				free(tmp->command);
			free(tmp);
		}
	}
	free(*shell);
}

void free_error(char *comment, t_shell **shell)
{
	free_shell(shell);
	lite_error(comment);
}
