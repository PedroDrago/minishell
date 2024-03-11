/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:11:32 by rafaelro          #+#    #+#             */
/*   Updated: 2024/03/11 19:41:53 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

char	**split_keyvalue(char *str, char sep)
{
	char	**splited;
	int		j;
	int		i;

	if (!str)
		return (NULL);
	splited = (char **)malloc(sizeof(char *) * 3);
	if (!splited)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	splited[0] = ft_substr(str, j, i);
	if (!splited[0])
		return (free_split(splited), NULL);
	i++;
	j = i;
	while (str[i])
		i++;
	splited[1] = ft_substr(str, j, i);
	if (!splited[1])
		return (free_split(splited), NULL);
	splited[2] = NULL;
	return (splited);
}

void	free_env(t_env *env)
{
	t_env	*temp_env;

	temp_env = env;
	while (env)
	{
		free(env->key);
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

t_env	*fill_env_struct(int fd)
{
	t_env	*env_head;
	t_env	*temp_env;
	char	*str;
	char	**args;

	str = get_next_line(fd);
	temp_env = NULL;
	while (str)
	{
		args = split_keyvalue(str, '=');
		if (!args)
		{
			free_env(env_head);
			return (NULL);
		}
		if (!temp_env)
		{
			env_head = make_new_env_node(args[0], args[1]);
			//FIX:deveriamos checar se make_new_env_node() der NULL, e retornar? 
			//N entendi se a função ja lida com isso de outra forma, pq parece que o looping espera que temp_env seja nulo eventualmente
			temp_env = env_head;
		}
		else
			temp_env->next = make_new_env_node(args[0], args[1]);
			//FIX:deveriamos checar se make_new_env_node() der NULL, e retornar? 
			//N entendi se a função ja lida com isso de outra forma, pq parece que o looping espera que temp_env seja nulo eventualmente
		free(args);
		free(str);
		str = get_next_line(fd);
		if (temp_env->next)
			temp_env = temp_env->next;
	}
	close(fd);
	return (env_head);
}

void	env(t_env *env, int fd_out)
{
	while (env)
	{
		ft_putstr_fd(env->key, fd_out);
		ft_putchar_fd('=', fd_out);
		ft_putstr_fd(env->value, fd_out);
		ft_putchar_fd('\n', fd_out);
		env = env->next;
	}
}

t_env	*get_env_node(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp(key, temp->key, ft_strlen(key) + 1))
			return (temp);
		temp = temp->next;
	}
	return (NULL); // WARN: here maybe we should return an empty string instead of null
}

int	set_env_value(t_env *env, char *key, char *value)
{
	t_env	*temp;
	t_env	*target_node;
	char	*new_value;

	target_node = get_env_node(env, key);
	if (!target_node)
	{
		temp = env;
		while (temp->next)
			temp = temp->next;
		temp->next = make_new_env_node(key, value);
		if (!temp->next)
			return (0);
		return (1);
	}
	new_value = ft_strdup(value);
	if (!new_value)
		return (0);
	free(target_node->value);
	target_node->value = new_value;
	return (1);
}

t_env	*load_envs(char *envp[])
{
	t_env	*env;
	char	**args;
	
	env = NULL;
	while (envp && *envp)
	{
		args = split_keyvalue(*envp, '='); //VALIDAR MALLOC
		if (!env)
			env = make_new_env_node(args[0], args[1]); //VALIDAR MALLOC
		else
			set_env_value(env, args[0], args[1]); //VALIDAR MALLOC?
		envp++;
		free(args);
	}
	return (env);
}
