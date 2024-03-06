#include "../includes/minishell.h"
#include <stdlib.h>

char	*parse_path(char *str)
{
	char	*new_path;
	char	*last_bar;
	int		count;

	if (*str == '.')
		str++;
	last_bar = ft_strrchr(str, '/');
	new_path = str;
	count = 0;
	while (new_path != last_bar)
	{
		count++;
		new_path++;
	}
	new_path = (char *)malloc(sizeof(char) * count + 2);
	if (!new_path)
		return (NULL);
	count = 0;
	while (str != (last_bar + 1))
		new_path[count++] = *str++;
	new_path[count] = '\0';
	return (new_path);
}

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

int	set_paths(t_shell *shell, char *execution_path)
{
	char	*pwd;
	char	*parsed_execution;

	pwd = get_cwd();
	if (!pwd)
		return (FALSE);
	parsed_execution = parse_path(execution_path);
	if (!parsed_execution)
		return (free(pwd), FALSE);
	if (parsed_execution[0] != '/')
	{
		pwd = ft_strjoin(pwd, "/", O_ONE);
		if (!pwd)
			return (free(parsed_execution), FALSE);
	}
	shell->shell_path = ft_strjoin(pwd, parsed_execution, O_BOTH);
	if (!shell->shell_path)
		return (free(pwd), free(parsed_execution), FALSE);
	shell->path = ft_strjoin(shell->shell_path, "bin", O_NONE);
	if (!shell->path)
		return (free(pwd), free(parsed_execution), FALSE);
	return (TRUE);
}

void	terminate_shell(t_shell *shell)
{
	free(shell->shell_path);
	free(shell->path);
	free_env(shell->env);
	free(shell);
}

int	append_path(t_shell *shell)
{
	char	*new_path;
	t_env	*old_path;

	old_path = get_env_node(shell->env, "PATH");
	new_path = ft_strjoin(shell->path, ":", O_NONE);
	new_path = ft_strjoin(new_path, old_path->value, O_ONE);
	set_env_value(shell->env, "PATH", new_path);
	return (TRUE);
}

t_shell	*init_shell(int argc, char *execution_path, char *envp[])
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		exit(EXIT_FAILURE); // NOTE: nada no programa foi mallocado nesse ponto, é seguro só dar exit
	if (!set_paths(shell, execution_path))
		return (free(shell), NULL);
	shell->env = load_envs(envp);
	if (!shell->env)
		return (free(shell->path), free(shell->shell_path), free(shell), NULL);
	shell->last_status = -99;
	(void)argc;
	append_path(shell);
	return (shell);
}
