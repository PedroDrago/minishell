#include "../includes/minishell.h"

char	*parse_path(char *str)
{
	char	*new_path;
	char	*last_bar;
	int	count;

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
	new_path = (char *) malloc (sizeof(char) * count + 2);
	if (!new_path)
		return (NULL);
	count = 0;
	while (str != (last_bar + 1))
	{
		new_path[count] = *str;
		str++;
		count++;
	}
	new_path[count] = '\0';
	return (new_path);
}

char	*get_pwd()
{
	char	*buffer;
	int		size;

	size = 200;
	buffer = (char *) malloc(sizeof(char) * size);
	if (!buffer)
		return (FALSE);
	while (!getcwd(buffer, size))
	{
		free(buffer);
		size += 100;
		buffer = (char *) malloc(sizeof(char) * size);
		if (!buffer)
			return (FALSE);
	}
	return (buffer);
}

int	set_paths(t_shell *shell, char *execution_path)
{
	char	*pwd;
	char	*parsed_execution;

	pwd = get_pwd();
	parsed_execution = parse_path(execution_path);
	if (parsed_execution[0] != '/')
		pwd = ft_strjoin(pwd, "/", O_ONE);
	shell->shell_path = ft_strjoin(pwd, parsed_execution, O_BOTH);
	shell->path = ft_strjoin(shell->shell_path, "bin/", O_NONE);
	return (TRUE);
}

int	init_shell(t_shell *shell, int argc, char *execution_path)
{
	char	*history_path;

	if (!set_paths(shell, execution_path))
		return (close(shell->history_fd), FALSE);
	history_path = ft_strjoin(shell->shell_path, "history", O_NONE);
	shell->history_fd = open(history_path, O_RDWR | O_APPEND | O_CREAT, 0777);
	free (history_path);
	if(shell->history_fd < 0)
		return (FALSE);
	(void) argc;
	return (TRUE);
}
