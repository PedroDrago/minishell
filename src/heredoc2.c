/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:57 by pdrago            #+#    #+#             */
/*   Updated: 2024/05/08 17:40:58 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	post_heredoc(int *pipe_fd, int *prevpipe)
{
	dup2(pipe_fd[0], *prevpipe);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
