#include "../minibash.h"

int	*signal_tracker(void)
{
	static int was_sig = 0;

	return (&was_sig);
}

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		prompt();
		*signal_tracker() = 1;
	}
}

void	set_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}