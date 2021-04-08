#include "../minibash.h"

/*
** "le" - string to move the cursor left one column
** "cd" - string to clear the line the cursor is on, and following lines
*/
void handle_up(t_shell *shell)
{
	size_t comm_len;

	if (!shell->hist_ptr->prev)
		return;
	comm_len = shell->hist_ptr->len;
	while (comm_len)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		comm_len--;
	}
	tputs(tgetstr("cd", 0), 1, ft_putchar);
	write(1, shell->hist_ptr->prev->command, shell->hist_ptr->prev->len);
	shell->hist_ptr = shell->hist_ptr->prev;
}

void handle_down(t_shell *shell)
{
	size_t comm_len;

	if (!shell->hist_ptr->next)
		return;
	comm_len = shell->hist_ptr->len;
	while (comm_len)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		comm_len--;
	}
	tputs(tgetstr("cd", 0), 1, ft_putchar);
	write(1, shell->hist_ptr->next->command, shell->hist_ptr->next->len);
	shell->hist_ptr = shell->hist_ptr->next;
}

/*
** "dc" - string to delete one character position at the cursor
*/
void handle_del(t_shell *shell)
{
	char *tmp;

	if (!shell->hist_ptr->len)
		return;
	tputs(tgetstr("le", 0), 1, ft_putchar);
	tputs(tgetstr("dc", 0), 1, ft_putchar);
	if ((shell->hist_ptr != shell->hist_curr) && !shell->hist_ptr->cache)
	{
		shell->hist_ptr->cache = ft_strdup(shell->hist_ptr->command);
		if (!shell->hist_ptr->cache)
			free_error(strerror(errno), &shell);
		shell->hist_ptr->cache_len = shell->hist_ptr->len;
	}
	shell->hist_ptr->command[--shell->hist_ptr->len] = '\0';
	tmp = shell->hist_ptr->command;
	shell->hist_ptr->command = ft_strdup(shell->hist_ptr->command);
	free(tmp);
}