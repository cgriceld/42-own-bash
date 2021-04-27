// #include <sys/types.h>
// #include <sys/wait.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <unistd.h>
#include <stdio.h>
// #include <string.h>
// #include <fcntl.h>

// int main(int argc, char **argv, char **envp)
// {
// 	pid_t	pid;
// 	int		res;
// 	int		status;
// 	int fd;

// 	char* arglist[] = {"./f1", NULL};
// 	pid = fork();
// 	if (!pid) // child process
// 	{
// 		// fd = open("file1.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 		// dup2(fd, 1);
// 		// close(fd);
// 		res = execve("./f1", arglist, envp);
// 		// printf("res : %d\n", res);
// 		// printf("errno : %d\n", errno);
// 		if (res < 0)
// 			printf("%s\n", strerror(errno));
// 		exit(res);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		printf("exit status : %d\n", WEXITSTATUS(status));
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 		return (1);
// 	}
// }

// int quo_syntax(char *str)
// {
// 	int doubled;
// 	int single;

// 	doubled = 0;
// 	single = 0;
// 	while (*str)
// 	{
// 		if (*str == '\"')
// 		{
// 			if (*(str - 1) == '\\' && !single && doubled)
// 				continue;
// 			if (!single && doubled)
// 				doubled--;
// 			else if (!single)
// 				doubled++;
// 		}
// 		else if (*str == '\'')
// 		{
// 			if (!doubled && single)
// 				single--;
// 			else if (!doubled)
// 				single++;
// 		}
// 		str++;
// 	}
// 	if (doubled || single)
// 		return (1);
// 	return (0);
// }

int main(void)
{
	if (!(0 % 2))
		printf("%s\n", "ok");
	return (0);
}