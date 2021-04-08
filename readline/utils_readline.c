#include "../minibash.h"

void set_mode(int type)
{
	struct termios term;

	tcgetattr(0, &term);
	!type ? (term.c_lflag &= ~(ECHO | ICANON)) : (term.c_lflag |= (ECHO | ICANON));
	tcsetattr(0, TCSANOW, &term);
}

void prompt(void)
{
	write(1, PROMPT, ft_strlen(PROMPT));
}

void init_hist(t_shell *shell)
{
	shell->hist_curr->command = ft_strdup("");
	if (!shell->hist_curr->command)
		free_error(strerror(errno), &shell);
	shell->hist_curr->cache = NULL;
	shell->hist_curr->len = 0;
	shell->hist_curr->cache_len = 0;
	shell->hist_curr->next = NULL;
}