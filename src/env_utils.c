/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:52 by pdrago            #+#    #+#             */
/*   Updated: 2024/05/09 19:20:06 by rafaelro         ###   ########.fr       */
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

int	set_env_value2(t_env *env, char *key, char *value)
{
	t_env	*target_node;
	char	*new_value;

	if (!key)
		return (0);
	target_node = get_env_node(env, key);
	if (!target_node)
		return (insert_new_node(env, key, value));
	free(key);
	free(target_node->value);
	if (value)
	{
		new_value = ft_strdup(value);
		free(value);
		if (!new_value)
			return (0);
	}
	else
		new_value = NULL;
	target_node->value = new_value;
	return (1);
}
