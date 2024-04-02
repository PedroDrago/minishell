#include "../includes/minishell.h"

int	is_heredoc(char *token)
{
	if (!ft_strncmp(token, "<<", 3))
		return (TRUE);
	return (FALSE);
}

int	do_heredoc(char *delimiter, int original_fd)
{
	int	pipe_fd[2];
	char *prompt;
	int	len;

	dup2(original_fd, 0);
	pipe(pipe_fd);
	prompt = readline("> ");
	if (!prompt)
		return (FALSE); // FIX: ????
	len = ft_strlen(delimiter);
	while (ft_strncmp(prompt, delimiter, len))
	{
		ft_putstr_fd(prompt, pipe_fd[1]); // FIX: ctrl+D e ctrl+C?
		ft_putstr_fd("\n", pipe_fd[1]);
		prompt = readline("> ");
		if (!prompt)
			return (FALSE); // FIX: ????
	}
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	return (TRUE);
}
