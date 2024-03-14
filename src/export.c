#include "../includes/minishell.h"
#include <stdio.h>

void	print_export(t_env *env, int fd_out)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(env->key, fd_out);
		ft_putchar_fd('=', fd_out);
		ft_putstr_fd(env->value, fd_out);
		ft_putchar_fd('\n', fd_out);
		env = env->next;
	}
}

int	is_valid(char *key)
{
	int i;

	i = -1;
	while (key[++i])
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (FALSE);
	return (TRUE);
}

int	export(t_node *node, t_shell *shell, int fd_out)
{
	int	i;
	char	**splited;

	if (split_len(node->args) == 1)
		return (print_export(shell->env, fd_out), 1);
	i = 0;
	while (node->args[i])
	{
		if (!ft_strchr(node->args[i], '=') && ++i)
			continue;
		splited = split_keyvalue(node->args[i], '=');
		if (!splited)
			return (1);
		if (!is_valid(splited[0]) && ++i)
		{
			printf("ERRO\n");
			continue;
		}
		if (!set_env_value(shell->env, splited[0], splited[1]))
			return (free_split(splited), 1);
		i++;
	}
	return (free_split(splited),0);
}
