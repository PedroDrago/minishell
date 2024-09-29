#include "../includes/minishell.h"

int	prep_process(t_node *node, t_shell *shell, int *prevpipe, int *pipefd)
{
	int	status;

	if (!node->splited_command)
	{
		free_process_data(shell);
		exit_safely(shell, 2);
	}
	if (!node->next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		dup2(*prevpipe, 0);
		close(*prevpipe);
		while (wait(&status) != -1)
			;
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		dup2(*prevpipe, STDIN_FILENO);
		close(*prevpipe);
	}
	return (1);
}

void	post_process(pid_t pid, t_shell *shell, int *prevpipe, int *pipefd)
{
	close(pipefd[1]);
	close(*prevpipe);
	*prevpipe = pipefd[0];
	append_process(pid, shell);
}

int	execute_node(t_node *node, t_shell *shell, int *prevpipe)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	expand_arguments(node, shell);
	node->args = get_args(node->splited_command);
	set_exit_status(0, shell);
	kill(getpid(), SIGUSR2);
	if (node->splited_command && is_builtin(node->splited_command[0]))
		return (execute_builtin(node, shell, prevpipe, pipefd));
	perform_redirections(0, node->splited_command, shell, prevpipe);
	pid = fork();
	if (pid == 0)
	{
		prep_process(node, shell, prevpipe, pipefd);
		execute_command(shell, node->args);
	}
	post_process(pid, shell, prevpipe, pipefd);
	if (!node->next)
		close(pipefd[0]);
	return (TRUE);
}

void	append_process(pid_t pid, t_shell *shell)
{
	shell->pids.array[shell->pids.index++] = pid;
}

void	init_processes_data(t_list *list, t_shell *shell)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = list->head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	shell->pids.array = malloc(sizeof(pid_t) * i);
	shell->pids.size = i;
	shell->pids.index = 0;
}
