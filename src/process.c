#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>


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
		append_process(pid, shell);
}

void	remove_empty_args(t_node *node)
{
	int	i;
	int	j;
	int	emptys;
	char	**new_args;

	i = -1;
	emptys = 0;
	while(node->args[++i])
		if (ft_strlen(node->args[i]) == 0)
			emptys++;
	new_args = malloc(sizeof(char *) * (i - emptys + 1));
	if (!new_args)
		exit(1);
	i = 0;
	j = 0;
	while(node->args[i])
	{
		if (ft_strlen(node->args[i]) == 0 && ++i)
			continue;
		new_args[j++] = ft_strdup(node->args[i++]);
	}
	new_args[j] = NULL;
	free_split(node->args);
	node->args = new_args;
}

int	execute_node(t_node *node, t_list *list, t_shell *shell)
{
	pid_t	pid;

	node->args = get_args(node->splited_command);
	expand_arguments(node, shell);
	remove_empty_args(node);
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

void	append_process(pid_t pid, t_shell *shell)
{
	shell->pids.array[shell->pids.index++] = pid;
}

void	free_process_data(t_shell *shell)
{
	free(shell->pids.array);
	shell->pids.index = 0;
	shell->pids.size = 0;
}

void	init_processes_data(t_list *list, t_shell *shell)
{
	int	i;
	t_node *tmp;

	i = 0;
	tmp = list->head;
	while(tmp)
	{
		if (!is_builtin(tmp->splited_command[0]))
			i++;
		tmp = tmp->next;
	}
	shell->pids.array = malloc(sizeof(pid_t) * i);
	shell->pids.size = i;
	shell->pids.index = 0;
}
