#include "../includes/minishell.h"

int	is_pipe(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (TRUE);
	return (FALSE);
}

void	execute_pipe(t_node *current, t_shell *shell, int *old_yield, int *new_yield)
{
	dup2(old_yield[0], 0);
	dup2(new_yield[1], 1);
	close(old_yield[0]);
	close(old_yield[1]);
	close(new_yield[1]);
	close(new_yield[0]);
	execute_command(shell, current);
}

int	*pipe_output(t_node *current, int *old_yield, t_shell *shell)
{
	int	pid;
	int	status;
	int	*new_yield;

	status = -1;
	new_yield = (int *)malloc(sizeof(int) * 2);
	if (!new_yield)
		return (NULL);
	if (pipe(new_yield) < 0)
		return (free(new_yield), NULL);
	if (is_builtin(current->command))
		exec_builtin(current, shell, new_yield[1]);
	else
	{
		pid = fork();
		if (pid == 0)
			execute_pipe(current, shell, old_yield, new_yield);
		else
		{
			close(old_yield[0]);
			close(old_yield[1]);
			free(old_yield);
			waitpid(pid, &status, 0);
			if (status > 0)
				printf("%s: command not found\n", current->command);
		}
	}
	return (new_yield);
}
