/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:09 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:38:14 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(t_env *env, int fd_out)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(env->key, fd_out);
		if (env->value)
		{
			ft_putchar_fd('=', fd_out);
			if (ft_strlen(env->value) > 1)
				ft_putstr_fd(env->value, fd_out);
			else
				ft_putstr_fd("\"\"", fd_out);
		}
		ft_putchar_fd('\n', fd_out);
		env = env->next;
	}
}

int	is_valid(char *key)
{
	int	i;

	i = -1;
	while (key[++i])
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (FALSE);
	return (TRUE);
}

int	export(char *argv[], t_shell *shell)
{
	int		i;
	char	**splited;

	if (split_len(argv) == 1)
		return (print_export(shell->env, 1), 1);
	i = 1;
	splited = NULL;
	while (argv[i])
	{
		splited = split_keyvalue(argv[i], '=');
		if (!splited)
			return (1);
		if (!is_valid(splited[0]) && ++i)
		{
			printf("ERRO\n");
			ft_putstr_fd("Erro PLACEHOLDER!!!!!!\n", 1);
			continue ;
		}
		if (!set_env_value(shell->env, splited[0], splited[1]))
			return (free_split(splited), 1);
		i++;
	}
	if (splited)
		free(splited);
	return (0);
}
