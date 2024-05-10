/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:36:07 by pdrago            #+#    #+#             */
/*   Updated: 2024/05/09 18:36:08 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_redirect_output(t_shell *shell, char *file, int status)
{
	free(file);
	exit_safely(shell, status);
}
