#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void	puterr(char *string, char *opt)
{
	while (*string)
		write(2, string++, 1);
	if (opt)
	{
		while (*opt)
			write(2, opt++, 1);
	}
	write(2, "\n", 1);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	fd[2];
	int	i;
	int	tmpfd;

	i = 0;
	tmpfd = dup(STDIN_FILENO);
	while (argv[i])
	{
		argv = &argv[i + 1];
		puterr(argv[0], NULL);
		
		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		
		// if (i == 0)
		// 	puterr("error: fatal");
		// puterr(argv[0], NULL);
		if (strcmp(argv[0], "cd") == 0)
		{
			if (i > 2)
				puterr("error: cd: bad arguments", NULL);
			else
			{
				if (chdir(argv[1]) != 0 )
					puterr("error: cd: cannot change directory to ", argv[1]);
			}
		}
		else if (argv[i] == NULL || strcmp(argv[i], ";"))
		{
			if (fork() == 0)
			{
				argv[i] = NULL;
				close(tmpfd);
				if (execve(argv[0], argv, envp) == -1)
					puterr("error: cannot execute ", argv[0]);
			}
			else
			{
				waitpid(-1, NULL, WUNTRACED);
			}
		}
		//TODO: pipe: "|"
	}
}