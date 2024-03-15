#include "../includes/minishell.h"
#include <unistd.h>

char *get_home_path(t_env *env)
{
	t_env *node;

	node = get_env_node(env, "HOME");
	if (!node)
		return (write(2, "Minishell: cd: HOME not set\n", 28), NULL);
	return(node->value);
}

int	cd(t_node *node, t_shell *shell)
{
	char *cwd;
	char *path;

	if (split_len(node->args) > 2)
		return (write(2, "Minishell: cd: too many arguments\n", 34), 1);
	cwd = get_cwd();
	if (!cwd)
		return (1);
	path = node->args[1];
	if (split_len((node->args)) == 1)
		path = get_home_path(shell->env);
	if (!path)
		return (1);
	chdir(path);
	if (!set_env_value(shell->env, "OLDPWD" , cwd))
		return (free(cwd), 1);
	free(cwd);
	cwd = get_cwd();
	if (!cwd)
		return (1);
	if (!set_env_value(shell->env, "PWD" , cwd))
		return (free(cwd), 1);
	return (free(cwd), 0);
}
