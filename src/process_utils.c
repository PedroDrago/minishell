/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:05:05 by rafaelro          #+#    #+#             */
/*   Updated: 2024/05/08 15:33:57 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_process_data(t_shell *shell)
{
	free(shell->pids.array);
	shell->pids.array = NULL;
	shell->pids.index = 0;
	shell->pids.size = 0;
}
