#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void	append_process(pid_t pid, t_shell *shell, char *basic_command)
{
	t_process	*process;
	char	**splited;

	process = malloc(sizeof(t_process));
	if (!process)
		exit(1);
	process->pid = pid;
	splited = command_split(basic_command);
	process->command = ft_strdup(splited[0]);
	free_split(splited);
	shell->processes_data.processes[shell->processes_data.index++] = process;
}

int	prep_process(t_node *node)
{
	if (!node->splited_command)
		exit(1);
	if (node->has_pipe)
		dup2(node->node_pipe[1], 1);
	if (node->prev && node->prev->has_pipe)
		dup2(node->node_pipe[0], 0);
	return (perform_redirections(node->splited_command));
}

void	post_process(pid_t pid, t_node *node, t_shell *shell)
{
		if (node->has_pipe)
			close(node->node_pipe[1]);
		if (node->prev && node->prev->has_pipe)
			close(node->node_pipe[0]);
		append_process(pid, shell, node->basic_command);
}

int	execute_node(t_node *node, t_list *list, t_shell *shell)
{
	pid_t	pid;

	node->args = get_args(node->splited_command);
	expand_arguments(node, shell);
	if (node->splited_command && is_builtin(node->splited_command[0]))
	{
		execute_builtin(node, shell);
		return (TRUE);
	}
	kill(getpid(), SIGUSR2);
	pid = fork();
	if (pid == 0)
	{
		if (!prep_process(node))
			exit(2);
		execute_command(shell, node->args);
	}
	else
	{
		post_process(pid, node, shell);
	}
	(void) list;
	return (TRUE);
}

void	free_process_data(t_shell *shell)
{
	int	i;

	i = 0;
	while(i < shell->processes_data.size)
	{
		free(shell->processes_data.processes[i]->command);
		free(shell->processes_data.processes[i]);
		i++;
	}
	free(shell->processes_data.processes);
}
void	init_processes_data(t_list *list, t_shell *shell)
{
	int	i;
	t_node *tmp;

	tmp = list->head;
	i = 0;
	while(tmp)
	{
		if (!is_builtin(tmp->splited_command[0]))
			i++;
		tmp = tmp->next;
	}
	shell->processes_data.processes = malloc(sizeof(t_process *) * i);
	shell->processes_data.size = i;
	shell->processes_data.index = 0;
}
