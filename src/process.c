#include "../includes/minishell.h"

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

void	prep_process(t_node *node, char ***args, t_shell *shell)
{
	if (!node->splited_command)
		exit(1);
	expand_arguments(node, shell);
	*args = get_args(node->splited_command);
	if (node->has_pipe)
		dup2(node->node_pipe[1], 1);
	if (node->prev && node->prev->has_pipe)
		dup2(node->node_pipe[0], 0);
	perform_redirections(node->splited_command);
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
	char	**args;
	pid_t	pid;

	if (is_builtin(node->splited_command[0]))
	{
		execute_builtin(node, shell);
		return (TRUE);
	}
	pid = fork();
	if (pid == 0)
	{
		prep_process(node, &args, shell);
		execute_command(shell, node->splited_command[0], args);
	}
	else
	{
		post_process(pid, node, shell);
	}
	(void) list;
	return (TRUE);
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
