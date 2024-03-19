#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	print_result(int fd)
{
	char	*gnl;
	char	*str;

	gnl = get_next_line(fd);
	str = ft_calloc(1, 1);
	if (!str)
	{
		if (gnl)
			free(gnl);
		return ;
	}
	while (gnl)
	{
		str = ft_strjoin(str, gnl, O_BOTH);
		gnl = get_next_line(fd);
	}
	close(fd);
	printf("%s", str);
	free(str);
}

int	execute_command(t_shell *shell, t_node *current)
{
	char	**paths;
	char	*path;
	int		count;

	execv(current->command, current->args);
	paths = ft_split(get_env_node(shell->env, "PATH")->value, ':');
	count = 0;
	while (paths[count])
	{
		path = ft_strjoin(paths[count], "/", O_NONE);
		path = ft_strjoin(path, current->command, O_ONE);
		execv(path, current->args);
		free(path);
		count++;
	}
	free_split(paths);
	exit(EXIT_FAILURE);
}

int	evaluate_pipeline(t_node *current, t_shell *shell)
{
	int	*yield;

	yield = (int *)malloc(sizeof(int) * 2);
	if (!yield)
		return (FALSE);
	if (pipe(yield) < 0)
		return (free(yield), FALSE);
	while (current)
	{
		if (!current->token || is_pipe(current->token))
			yield = pipe_output(current, yield, shell);
		else if (is_redirect_output(current->token))
		{
			redirect_output(current, shell, yield);
			current = current->next;
		}
		current = current->next;
	}
	close(yield[1]);
	print_result(yield[0]);
	free(yield);
	return (TRUE);
}

void	set_exit_status(int status, t_shell *shell)
{
	char	*status_string;

	status_string = ft_itoa(status);
	if (!status_string)
		exit_safely(shell);
	if (!set_env_value(shell->env, "?", status_string))
		exit_safely(shell);
	free(status_string);
}

void	evaluate_solo(t_node *current, t_shell *shell)
{
	int	pid;
	int	status;

	if (is_builtin(current->command))
		exec_builtin(current, shell, 1);
	else
	{
		pid = fork();
		g_pid = pid;
		if (pid == 0)
			execute_command(shell, current);
		waitpid(pid, &status, 0);
		set_exit_status(status, shell);
		if (status > 0 && WTERMSIG(status) != SIGINT)
			printf("%s: command not found\n", current->command);
	}
}

int    evaluate_prompt(char *prompt, t_shell *shell)
{
	t_list    *prompt_list;
	t_node *current;

	prompt_list = generate_list(prompt, shell);
	if (!prompt_list)
		return (FALSE);
	shell->prompt_list = prompt_list;
	current = prompt_list->head;
	if (!current->token)
		evaluate_solo(current, shell);
	else
		if (!evaluate_pipeline(current, shell))
			return (free_list(prompt_list), FALSE);
	free_list(prompt_list);
	shell->prompt_list = NULL;
	return (TRUE);
}
