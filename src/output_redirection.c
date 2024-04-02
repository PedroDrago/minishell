/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:21 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:46:09 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
// #include <unistd.h>


// int	open_output_file(t_node *node)
// {
// 	int	file;
//
// 	if (!node->next || !node->next->command
// 		|| !ft_strlen(node->next->command))
// 		return (printf("minishell: Syntax error\n"), -1);
// 	if (!ft_strncmp(node->token, ">", 2))
// 		file = open(node->next->command, O_RDWR | O_TRUNC | O_CREAT, 0664);
// 	else
// 		file = open(node->next->command, O_RDWR | O_APPEND | O_CREAT, 0664);
// 	if (file < 0)
// 		return (-1);
// 	return (file);
// }
//
// void	redirect_output(t_node *node, t_shell *shell)
// {
// 	int	file;
//
// 	file = open_output_file(node);
// 	if (file < 0)
// 		return ; // FIX: deu merda pra abrir
// 	if (is_builtin(node->command))
// 	{
// 		exec_builtin(node, shell, file);
// 		return ;
// 	}
// 	g_pid = fork();
// 	if (g_pid == 0)
// 	{
// 		dup2(file, 1);
// 		execute_command(shell, node);
// 		exit(1);
// 	}
// 	else
// 	{
// 		shell->pids->p_array[shell->pids->index] = g_pid;
// 		shell->pids->c_array[shell->pids->index++] = node->command;
// 	}
// }
