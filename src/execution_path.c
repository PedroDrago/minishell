#include "../includes/minishell.h"

char **get_paths_split(t_shell *shell)
{
	char	**splited;
	t_env	*node;

	node = get_env_node(shell->env, "PATH");
	if (!node || !node->value)
		return (NULL);
	splited = ft_split(node->value, ':');
	if (!splited)
		return (NULL);
	return (splited);
}

char *get_current_path_str(char *path, char *command)
{
	char	*joined;

	joined = ft_strjoin(path, "/", O_ONE);
	if (!joined)
		return(NULL);
	joined = ft_strjoin(joined, command, O_ONE);
	if (!joined)
		return(NULL);
	return (joined);
}

int	can_open_file(int stat_return, struct stat *file_info, char *command)
{
	if (stat_return < 0)
		return (0);
	if (!(file_info->st_mode & S_IXUSR))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	return (1);
}


char	*get_right_path(t_shell *shell, char *command) //FIX: Leak? Child process
{
	char	*path;
	char	**paths_split;
	int	i;
	struct stat	file_info; 

	i = 0;
	paths_split = get_paths_split(shell);
	if (!paths_split)
		return (NULL);
	while(paths_split[i])
	{
		path = get_current_path_str(paths_split[i++], command);
		if (can_open_file(stat(path, &file_info), &file_info, command))
			return (path);
		free(path);
	}
	free(paths_split);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": Command not found\n", 2);
	free_before_safely_exit(shell);
	exit(127);
}
