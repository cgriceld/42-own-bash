#include "minibash.h"

// static void	prepare(int argc, t_shell **shell)

static void	prepare(int __attribute__((unused)) argc, t_shell **shell)
{
	// if (argc != 1)
	// 	lite_error(WRONG_ARGS);
	*shell = (t_shell *)malloc(sizeof(t_shell));
	if (!*shell)
		lite_error(strerror(errno));
	(*shell)->env = NULL;
	(*shell)->seq = NULL;
	(*shell)->history = (t_history *)malloc(sizeof(t_history));
	if (!(*shell)->history)
		free_error(strerror(errno), shell);
	(*shell)->history->prev = NULL;
	(*shell)->hist_curr = (*shell)->history;
	(*shell)->hist_ptr = (*shell)->hist_curr;
	init_hist(*shell);
	ret_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	tgetent(NULL, getenv("TERM"));
	ret_status = 0;
	prepare(argc, &shell);
	envp_to_list(envp, shell);
	set_signals();
	if (argc == 3)
	{
		shell->hist_curr->command = ft_strdup(argv[2]);
		parser(shell);
	}
	else
		ft_readline(shell);
	free_error(NULL, &shell);
	return (ret_status);
}

// int			main(int argc, char __attribute__((unused)) **argv, char **envp)