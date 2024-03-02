/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:11:32 by rafaelro          #+#    #+#             */
/*   Updated: 2024/03/01 23:57:48 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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
	value[ft_strlen(value) - 1] = '\0';
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

void	put_envs(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(env->value, 1);
		ft_putchar_fd('\n', 1);
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
	return (NULL);
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

t_env	*load_envs(void)
{
	t_env	*env;
	int		fd[2];
	int		pid;
	char	**args;

	args = ft_split("env", ' ');
	if (!args)
		return (NULL);
	if (pipe(fd) < 0)
		return (free_split(args), NULL);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]) ;
		close(fd[1]);
		execv("/bin/env", args);
	}
	if (pid > 0) //NOTE: se o fork() acima der errado a gnt n da wait pra n ficar preso num deadlock
		wait(NULL);
	free_split(args);
	close(fd[1]);
	env = fill_env_struct(fd[0]);
	return (env);
}
