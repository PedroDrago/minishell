#include "../includes/minishell.h"
#include <stdio.h>

void	free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

int	remove_node(t_env **env, char *key)
{
	t_env *previous;
	t_env *current;
	t_env *tmp;


	if (!ft_strncmp((*env)->key, key, ft_strlen(key)))
	{
		tmp = *env;
		*env = (*env)->next;
		free_node(tmp);
		return (0);
	}
	previous = *env;
	current = previous->next;
	while (current)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key)))
		{
			previous->next = current->next;
			return (free_node(current), 0);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

int	unset(t_node *current, t_shell *shell)
{
	int	i;

	i = 1;
	while (current->args[i])
	{
		if (ft_strchr(current->args[i], '?') && ++i)
			continue;
		remove_node(&shell->env, current->args[i++]);
	}
	return (0);
}
