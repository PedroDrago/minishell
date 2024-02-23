#include "../includes/minishell.h"
#include <unistd.h>

void	print_result(int fd)
{
	char *gnl;
	char *str;

	gnl = get_next_line(fd);
	str = ft_calloc(1, 1);
	while (gnl)
	{
		str = ft_strjoin(str, gnl, O_BOTH);
		gnl = get_next_line(fd);
	}
	close(fd);
	printf("%s", str);
	free (str);
}

int *pipe_command(t_node *current, int *old_yield)
{
	char *path;
	int pid;
	int *new_yield;

	new_yield = (int *) malloc(sizeof(int) * 2);
	pipe(new_yield);
	pid = fork();
	if (pid == 0)
	{
		dup2(old_yield[0], 0);
		dup2(new_yield[1], 1);
		close(old_yield[0]);
		close(old_yield[1]);
		close(new_yield[1]);
		close(new_yield[0]);
		path = ft_strjoin("/bin/", current->command, O_NONE);
		execv(path, current->args);
	}
	else
	{
		close(old_yield[0]);
		close(old_yield[1]);
		free(old_yield);
		waitpid(pid, NULL, 0);
	}
	return (new_yield);
}

int    evaluate_prompt(char *prompt, t_shell *shell)
{
	t_list    *prompt_list;
	t_node	*current;
	int *yield;

	prompt_list = generate_list(prompt);
	if (!prompt_list)
		return (FALSE);
	current = prompt_list->head;
	yield = (int *) malloc (sizeof(int) * 2);
	pipe(yield);
	while (current)
	{
		yield = pipe_command(current, yield);
		current = current->next;
	}
	close(yield[1]);
	print_result(yield[0]);
	(void) shell;
	return (TRUE);
}
