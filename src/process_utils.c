#include "../includes/minishell.h"

void	free_process_data(t_shell *shell)
{
	free(shell->pids.array);
	shell->pids.array = NULL;
	shell->pids.index = 0;
	shell->pids.size = 0;
}
