#include "../includes/minishell.h"

int	is_heredoc(char *token)
{
	if (!ft_strncmp(token, "<<", 3))
		return (TRUE);
	return (FALSE);
}

void	sighandler(int sig)
{
	close(0);
	(void) sig;
}

int	do_heredoc(char *del, int prevpipe, t_shell *shell)
{
	char	*prompt;
	int		pid;

	pid = fork();
	del = uncontrol_arg(del);
	if (pid == 0)
	{
		signal(SIGINT, sighandler);
		while (TRUE)
		{
			prompt = readline("> ");
			if (!prompt || !ft_strncmp(prompt, del, ft_strlen(del) + 1))
				break ;
			ft_putendl_fd(prompt, prevpipe);
		}
		close(prevpipe);
		free(del);
		exit_ultra_safe(shell);
	}
	waitpid(pid, 0, 0);
	free(del);
	return (TRUE);
}

void	exit_heredoc(t_shell *shell, int status)
{
	free_process_data(shell);
	exit_safely(shell, status);
}

void	do_heredoc_builtin(char *delimiter, int original_fd, t_shell *shell)
{
	char	*prompt;
	int		len;

	signal(SIGINT, sighandler);
	dup2(original_fd, 1);
	prompt = readline("> ");
	if (!prompt)
		exit_heredoc(shell, 1);
	delimiter = uncontrol_arg(delimiter);
	len = ft_strlen(delimiter);
	while (ft_strncmp(prompt, delimiter, len + 1))
	{
		prompt = readline("> ");
		if (!prompt)
		{
			free(delimiter);
			exit_heredoc(shell, 1);
		}
	}
	free(delimiter);
	exit_heredoc(shell, 0);
}
