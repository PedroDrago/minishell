/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_setting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:42 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:38:40 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cwd(void)
{
	char	*buffer;
	int		size;

	size = 200;
	buffer = (char *)malloc(sizeof(char) * size);
	if (!buffer)
		return (FALSE);
	while (!getcwd(buffer, size))
	{
		free(buffer);
		size += 100;
		buffer = (char *)malloc(sizeof(char) * size);
		if (!buffer)
			return (FALSE);
	}
	return (buffer);
}

t_shell	*init_shell(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	shell->envp = envp;
	signal(SIGINT, exit_program);
	if (!shell)
		exit(EXIT_FAILURE);
	shell->env = load_envs(envp);
	if (!shell->env)
		return (free(shell), NULL);
	shell->last_status = -99;
	shell->prompt_string = NULL;
	shell->prompt_list = NULL;
	(void)argc, (void)argv;
	return (shell);
}
