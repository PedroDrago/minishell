/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:43 by pdrago            #+#    #+#             */
/*   Updated: 2024/04/12 12:00:57 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

char	*get_home_path(t_env *env)
{
	t_env	*node;

	node = get_env_node(env, "HOME");
	if (!node)
		return (write(2, "Minishell: cd: HOME not set\n", 28), NULL);
	return (node->value);
}

int	duplicate_env_key_if_needed(t_env *env, char *key, char *value)
{
	if (!get_env_node(env, key))
	{
		if (set_env_value(env, ft_strdup(key), ft_strdup(value)))
			return(1);
		return (0);
	}
	if (set_env_value(env, key, value))
		return (1);
	return (0);
}

int	cd(char *argv[], t_shell *shell)
{
	char	*cwd;
	char	*path;

	if (split_len(argv) > 2)
	{
		set_exit_status(1, shell);
		return (write(2, "Minishell: cd: too many arguments\n", 34), 1);
	}
	cwd = get_cwd();
	if (!cwd)
		return (1);
	path = argv[1];
	if (split_len((argv)) == 1 || !ft_strncmp(argv[1], "~", 2))
		path = get_home_path(shell->env);
	if (!path)
		return (1);
	if (chdir(path) < 0)
	{
		perror("Minishell: cd");
		set_exit_status(1, shell);
	}
	if (!duplicate_env_key_if_needed(shell->env, "OLDPWD", cwd))
		return (free(cwd), 1);
	free(cwd);
	cwd = get_cwd();
	if (!cwd)
		return (1);
	if (!duplicate_env_key_if_needed(shell->env, "PWD", cwd))
		return (free(cwd), 1);
	return (free(cwd), 0);
}
