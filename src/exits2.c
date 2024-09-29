#include "../includes/minishell.h"

void	exit_redirect_output(t_shell *shell, char *file, int status)
{
	free(file);
	exit_safely(shell, status);
}
