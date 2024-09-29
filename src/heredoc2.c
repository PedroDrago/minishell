#include "../includes/minishell.h"

void	post_heredoc(int *pipe_fd, int *prevpipe)
{
	dup2(pipe_fd[0], *prevpipe);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
