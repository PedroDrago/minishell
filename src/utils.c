/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:59 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:38:48 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

void	set_exit_status(int status, t_shell *shell)
{
	char	*status_string;

	status_string = ft_itoa(status);
	if (!status_string)
		exit_safely(shell);
	if (!set_env_value(shell->env, "?", status_string))
		exit_safely(shell);
	free(status_string);
}

void	free_split(char **splited)
{
	int	count;

	count = -1;
	if (!splited)
		return ;
	while (splited[++count])
		free(splited[count]);
	free(splited);
}

void	print_split(char **argv)
{
	int	i;

	i = 0;
	printf("**********SPLIT START***********\n");
	while (argv && argv[i])
		printf("!%s!\n", argv[i++]);
	printf("**********SPLIT END***********\n");
}

void	free_list(t_list *list)
{
	t_node	*tmp;

	while (list->head)
	{
		if (list->head->command)
			free(list->head->command);
		if (list->head->token)
			free(list->head->token);
		if (list->head->args)
			free_split(list->head->args);
		tmp = list->head;
		list->head = list->head->next;
		free(tmp);
	}
	free(list);
}

void	print_list(t_list *arg)
{
	t_node	*tmp;

	tmp = arg->head;
	while (tmp)
	{
		printf("command string: %s\n", tmp->basic_command);
		printf("Has pipe: %i\n", tmp->has_pipe);
		tmp = tmp->next;
	}
}
