/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:55 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:38:45 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

int	remove_node(t_env **env, char *key)
{
	t_env	*previous;
	t_env	*current;
	t_env	*tmp;

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

int	unset(char *argv[], t_shell *shell)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '?') && ++i)
			continue ;
		remove_node(&shell->env, argv[i++]);
	}
	return (0);
}
