#include "../includes/minishell.h"

int	cd(t_node *node, t_shell *shell)
{
	char *cwd;

	cwd = get_cwd();
	if (!cwd)
		return (1);
	if (!set_env_value(shell->env, "OLDPWD" , cwd))
		return (free(cwd), 1);
	free(cwd);
	chdir(node->args[1]);
	cwd = get_cwd();
	if (!cwd)
		return (1);
	if (!set_env_value(shell->env, "PWD" , cwd))
		return (free(cwd), 1);
	return (free(cwd), 0);
}
