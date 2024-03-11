#include "../includes/minishell.h"

int	is_redirect_output(char *token)
{
	if (!ft_strncmp(token, ">", 2) || !(ft_strncmp(token, ">>", 3)))
		return (TRUE);
	return (FALSE);
}

void	execute_redirection(t_node *current, t_shell *shell, int *old_yield, int file)
{
	dup2(old_yield[0], 0);
	dup2(file, 1);
	close(old_yield[0]);
	close(old_yield[1]);
	close(file);
	execute_command(shell, current);
}

void	redirect_output(t_node *current, t_shell *shell, int *old_yield)
{
	int		file;
	int		pid;
	int status;

	if (!current->next || !current->next->command
		|| !ft_strlen(current->next->command))
		printf("minishell: Syntax error\n");
	if (!ft_strncmp(current->token, ">", 2))
		file = open(current->next->command, O_RDWR | O_TRUNC | O_CREAT, 0777);
	else
		file = open(current->next->command, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (file < 0)
		return ;
	pid = fork();
	if (pid == 0)
		execute_redirection(current, shell, old_yield, file);
	else
	{
		close(old_yield[0]);
		close(old_yield[1]);
		close(file);
		waitpid(pid, &status, 0);
		if (status > 0)
			printf("%s: command not found\n", current->command);
	}
}
