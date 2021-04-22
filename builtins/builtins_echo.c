#include "../minibash.h"

 int	builtins_echo(t_shell *shell, t_seq *tmp_seq)
{
	int n;
	int i;

	ret_status = 0;
	n = 0;
	i = 0;
	if (ft_strncmp(ft_strtrim(tmp_seq->args[1], "\n"), "-n", 3) == 0)
		n = 1;
	while(tmp_seq->args[++i + n - 1] != NULL)
		printf("%s ", ft_strtrim(tmp_seq->args[i + n], "\n"));
	if (tmp_seq->args[i + n] != NULL)
		printf("%s", ft_strtrim(tmp_seq->args[i + n], "\n"));
	if (n == 0)
		printf("\n");
	return (ret_status);
}
