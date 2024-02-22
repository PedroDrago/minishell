#include "../includes/minishell.h"
#include <unistd.h>

int    evaluate(char *prompt, t_shell *shell)
{
	t_list    *prompt_list;

	prompt_list = generate_list(prompt);
	if (!prompt_list)
		return (FALSE);
	eval_pipe(prompt_list->head);
	(void) shell;
	return (TRUE);
}

int    eval_pipe(t_node *current)
{
	int fds[2];
	int pid;
	int pid2;

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
	dup2(fds[1], 1);
		close(fds[1]);
		close(fds[0]);
		char *path= ft_strjoin("/bin/", current->command, O_NONE);
		execv(path, current->args);
		free (path);
		return 0;
	}
	else
	{
		waitpid(pid, NULL, 0);
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(fds[0], 0);
			close(fds[1]);
			close(fds[0]);
			char *path= ft_strjoin("/bin/", current->next->command, O_NONE);
			execv(path, current->next->args);
			return 0;
		}
		else
		{
			close(fds[1]);
			close(fds[0]);
		waitpid(pid2, NULL, 0);
		}
	}
	return (1);
}
