#include "../includes/minishell.h"
#include <stdlib.h>

char	*get_cwd(void)
{
	char	*buffer;
	int		size;

	size = 200;
	buffer = (char *)malloc(sizeof(char) * size);
	if (!buffer)
		return (FALSE);
	while (!getcwd(buffer, size))
	{
		free(buffer);
		size += 100;
		buffer = (char *)malloc(sizeof(char) * size);
		if (!buffer)
			return (FALSE);
	}
	return (buffer);
}

t_shell	*init_shell(char *envp[])
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	signal(SIGINT, exit_program);
	if (!shell)
		exit(EXIT_FAILURE);
	shell->env = load_envs(envp);
	if (!shell->env)
		return (free(shell), NULL);
	shell->last_status = -99;
	shell->prompt_string = NULL;
	return (shell);
}
