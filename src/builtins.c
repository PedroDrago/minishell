#include "../includes/minishell.h"

void	perform_builtin_redirections(char **splited_com, int *status,
	int original_fd, t_shell *shell)
{
	while (*splited_com)
	{
		if (is_redirect_input(*splited_com))
		{
			*status = redirect_input_builtin(*(++splited_com));
			if (*status == 1)
				set_exit_status(1, shell);
		}
		else if (is_redirect_output(*splited_com))
		{
			*status = redirect_output_builtin(*splited_com, *(splited_com + 1));
			if (*status == 1)
				set_exit_status(1, shell);
		}
		else if (is_heredoc(*splited_com))
		{
			*status = fork();
			if (*status == 0)
				do_heredoc_builtin(*(++splited_com), original_fd, shell);
			waitpid(*status, status, 0);
		}
		++splited_com;
	}
}

int	is_builtin(char *command)
{
	if (!ft_strncmp(command, "echo", 5))
		return (TRUE);
	if (!ft_strncmp(command, "cd", 3))
		return (TRUE);
	if (!ft_strncmp(command, "pwd", 4))
		return (TRUE);
	if (!ft_strncmp(command, "export", 7))
		return (TRUE);
	if (!ft_strncmp(command, "unset", 6))
		return (TRUE);
	if (!ft_strncmp(command, "env", 4))
		return (TRUE);
	if (!ft_strncmp(command, "exit", 5))
		return (TRUE);
	return (FALSE);
}

int	prep_builtin(t_node *node, t_shell *shell, int *prevpipe, int *pipefd)
{
	int	status;
	int	original_fd;

	original_fd = dup(1);
	status = 0;
	if (!node->next)
	{
		close(pipefd[1]);
		close(pipefd[0]);
		close(*prevpipe);
	}
	else
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(*prevpipe);
	}
	perform_builtin_redirections(node->splited_command, &status,
		original_fd, shell);
	close(original_fd);
	uncontrol_args(node->args);
	return (status);
}

void	post_builtin(t_node *node, int *prevpipe, int *pipefd)
{
	if (node->next)
	{
		close(pipefd[1]);
		close(*prevpipe);
		*prevpipe = pipefd[0];
	}
}

int	execute_builtin(t_node *node, t_shell *shell, int *prevpipe,
		int *pipefd)
{
	int	status;

	status = prep_builtin(node, shell, prevpipe, pipefd);
	if (status)
		;
	else if (!ft_strncmp(node->splited_command[0], "echo", 5))
		status = echo(node->args);
	else if (!ft_strncmp(node->splited_command[0], "cd", 3))
		status = cd(node->args, shell);
	else if (!ft_strncmp(node->splited_command[0], "pwd", 4))
		status = pwd();
	else if (!ft_strncmp(node->splited_command[0], "export", 7))
		status = export(node->args, shell);
	else if (!ft_strncmp(node->splited_command[0], "unset", 6))
		status = unset(node->args, shell);
	else if (!ft_strncmp(node->splited_command[0], "env", 4))
		status = env(shell->env);
	else if (!ft_strncmp(node->splited_command[0], "exit", 5)
		&& (!node->prev && !node->next))
		free_and_exit_builtin(shell, node);
	post_builtin(node, prevpipe, pipefd);
	set_builtin_exit_status(shell, status);
	return (TRUE);
}
