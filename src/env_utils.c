/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:52 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:17:52 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_env *env)
{
	t_env	*temp_env;

	temp_env = env;
	while (env)
	{
		free(env->key);
		if (env->value)
			free(env->value);
		temp_env = env;
		env = env->next;
		free(temp_env);
	}
}

t_env	*make_new_env_node(char *key, char *value)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	return (new_env);
}

int	fill_node(char *str, int fd, t_env *temp_env, t_env *env_head)
{
	char	**args;

	temp_env = NULL;
	args = split_keyvalue(str, '=');
	if (!args)
	{
		free_env(env_head);
		return (FALSE);
	}
	if (!temp_env)
	{
		env_head = make_new_env_node(args[0], args[1]);
		temp_env = env_head;
	}
	else
		temp_env->next = make_new_env_node(args[0], args[1]);
	free(args);
	free(str);
	str = get_next_line(fd);
	return (TRUE);
}

t_env	*fill_env_struct(int fd)
{
	char	*str;
	t_env	*temp_env;
	t_env	*env_head;

	str = get_next_line(fd);
	env_head = NULL;
	while (str)
	{
		if (!fill_node(str, fd, temp_env, env_head))
			return (NULL);
		if (temp_env->next)
			temp_env = temp_env->next;
	}
	close(fd);
	return (env_head);
}
