/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:32 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:18:32 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_node_value(t_env *env, char *key)
{
	t_env	*node;

	node = get_env_node(env, key);
	if (!node)
		return (NULL);
	return (node->value);
}

char	*get_prompt_user(char *str, t_shell *shell)
{
	char	*user;

	str = ft_strjoin(str, "\e[1;32m", O_ONE);
	user = get_env_node_value(shell->env, "USER");
	if (!user)
		user = "username";
	str = ft_strjoin(str, user, O_ONE);
	str = ft_strjoin(str, "\e[0m:\e[1;34m", O_ONE);
	return (str);
}

char	*get_prompt_pwd(char *str, t_shell *shell)
{
	char	*pwd;
	char	*home;

	pwd = get_env_node(shell->env, "PWD")->value;
	pwd = get_env_node_value(shell->env, "PWD");
	if (!pwd)
		pwd = ".";
	home = get_env_node_value(shell->env, "HOME");
	if (home && !ft_strncmp(pwd, home, ft_strlen(pwd)))
		pwd = "~";
	str = ft_strjoin(str, pwd, O_ONE);
	str = ft_strjoin(str, "\e[0m$ ", O_ONE);
	return (str);
}

char	*get_prompt_string(t_shell *shell)
{
	char	*str;

	if (shell->prompt_string != NULL)
		free(shell->prompt_string);
	str = ft_calloc(1, 1);
	str = get_prompt_user(str, shell);
	str = get_prompt_pwd(str, shell);
	shell->prompt_string = str;
	return (str);
}

char	*get_prompt(t_shell *shell)
{
	char	*prompt;

	prompt = readline(get_prompt_string(shell));
	if (prompt == NULL)
		exit_safely(shell);
	while (prompt[ft_strlen(prompt) - (!!ft_strlen(prompt) * 1)] == '\\')
	{
		prompt[ft_strlen(prompt) - 1] = '\0';
		prompt = ft_strjoin(prompt, readline("> "), O_NONE);
		if (prompt == NULL)
			exit_safely(shell);
	}
	return (prompt);
}
