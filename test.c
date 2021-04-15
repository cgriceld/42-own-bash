#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		res;
	int		status;

	char* arglist[] = {"ls", NULL};
	pid = fork();
	if (!pid) // child process
	{
		res = execve("ls", arglist, envp);
		printf("res : %d\n", res);
		printf("errno : %d\n", errno);
		if (res < 0)
			printf("%s\n", strerror(errno));
		exit(res);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("exit status : %d\n", WEXITSTATUS(status));
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
}
