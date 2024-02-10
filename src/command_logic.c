#include "../includes/minishell.h"

int	fill_command(t_command *command, char **splited)
{
	int		count;
	char	*str;

	command->command = splited[0];
	str = ft_calloc(1, 1);
	count = 1;
	while (splited[count])
	{
		str = ft_strjoin(str, splited[count], O_ONE);
		str = ft_strjoin(str, " ", O_ONE);
		count++;
	}
	command->args = ft_split(str, ' ');
	free(str);
	return (TRUE);
}

int	execute_pwd(t_shell *shell, t_command command)
{
	int		pid;
	int		status;
	char	*path;

	path = ft_strjoin(shell->path, "pwd", O_NONE);
	pid = fork();
	if (pid < 0 || !path)
		return (FALSE);
	if (pid == 0)
		execve(path, command.args, NULL);
	wait(&status);
	shell->last_status = status;
	free (path);
	return (TRUE);
}

int	execute_cd(t_shell *shell, t_command command)
{
	shell->last_status = 0;
	if (chdir(command.args[0]) < 0)
	{
		printf("cd: no such file or directory: %s\n", command.args[0]);
		shell->last_status = 1;
	}
	return (TRUE);
}

int	execute_echo(t_shell *shell, t_command command)
{
	int		pid;
	int		status;
	char	*path;

	path = ft_strjoin(shell->path, "echo", O_NONE);
	pid = fork();
	if (pid < 0 || !path)
		return (FALSE);
	if (pid == 0)
		execve(path, command.args, NULL);
	wait(&status);
	shell->last_status = status;
	free (path);
	return (TRUE);
}

int	resolve_command(t_command command, t_shell *shell)
{
	if (!ft_strncmp(command.command, "cd", 3))
		return (execute_cd(shell, command));
	else if (!ft_strncmp(command.command, "pwd", 4))
		return (execute_pwd(shell, command));
	else if (!ft_strncmp(command.command, "echo", 5))
		return (execute_echo(shell, command));
	else if (!ft_strncmp(command.command, "export", 7))
		;
	else if (!ft_strncmp(command.command, "env", 4))
		;
	else if (!ft_strncmp(command.command, "unset", 6))
		;
	else if (!ft_strncmp(command.command, "exit", 5))
		return (FALSE);
	else
		printf("%s: command not found\n", command.command);
	return (TRUE);
}
