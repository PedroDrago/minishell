#include "../includes/minishell.h"
#include <unistd.h>

int *single_eval(t_node *current, int *fds)
{
	char *path;
	int pid;
	int *yield;

	yield = (int *) malloc(sizeof(int) * 2);
	pipe(yield);
	pid = fork();
	if (pid == 0)
	{
		dup2(fds[0], 0);
		dup2(yield[1], 1);
		close(fds[0]);
		close(fds[1]);
		path = ft_strjoin("/bin/", current->command, O_NONE);
		execv(path, current->args);
	}
	else
	{
		close(fds[1]);
		close(fds[0]);
		waitpid(pid, NULL, 0);
	}
	return (yield);
}

int    evaluate(char *prompt, t_shell *shell)
{
	t_list    *prompt_list;
	t_node	*current;
	int *yield;

	prompt_list = generate_list(prompt);
	if (!prompt_list)
		return (FALSE);
	current = prompt_list->head;
	yield = double_eval(current);
	current = current->next;
	while (current)
	{
		yield = single_eval(current, yield);
		current = current->next;
	}
	//isso aqui abaixo foi apenas para testar se o output tava certo
	char *buffer = malloc(sizeof(char) * 500);
	int b = read(yield[0], buffer,  500);
	buffer[b] = '\0';
	printf("%s", buffer);
	(void) shell;
	return (TRUE);
}

int	*double_eval(t_node *current)
{
	int fds[2];
	int pid;
	int pid2;
	int *yield;

	yield = (int *) malloc (sizeof(int) * 2);
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
		pipe(yield);
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(fds[0], 0);
			dup2(yield[1], 1);
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
	return (yield);
}
