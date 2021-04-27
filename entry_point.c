#include "minibash.h"

static void	prepare(int argc, t_shell **shell)
{
	if (argc != 1)
		lite_error(WRONG_ARGS);
	*shell = (t_shell *)malloc(sizeof(t_shell));
	if (!*shell)
		lite_error(strerror(errno));
	(*shell)->env = NULL;
	(*shell)->seq = NULL;
	(*shell)->history = (t_history *)malloc(sizeof(t_history));
	if (!(*shell)->history)
		free_error(strerror(errno), shell);
	(*shell)->history->prev = NULL; // first node
	(*shell)->hist_curr = (*shell)->history;
	(*shell)->hist_ptr = (*shell)->hist_curr;
	init_hist(*shell);
	(*shell)->sep[0] = 0;
	(*shell)->sep[1] = 0;
}

int			main(int argc, char __attribute__((unused)) **argv, char **envp)
{
	t_shell	*shell;

	ret_status = 0;
	prepare(argc, &shell);
	envp_to_list(envp, shell);
	tgetent(NULL, getenv("TERM")); // can return -1 in error
	set_signals();
	ft_readline(shell);
	free_error(NULL, &shell);
	return (ret_status);
}