/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:13:45 by rafaelro          #+#    #+#             */
/*   Updated: 2024/05/07 19:55:22 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long long int	ft_atolli_mod(const char *nptr)
{
	long long int	total;
	long long int	signal;

	total = 0;
	signal = 1;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if ((*nptr == '-' || *nptr == '+') && *nptr++ == '-')
		signal *= -1;
	while (ft_isdigit(*nptr))
		total = total * 10 + (*nptr++ - '0');
	return (total * signal);
}

int	is_valid_lli(char *status)
{
	unsigned long long int	total;
	unsigned long long int	max_lli;
	int						signal;

	max_lli = 9223372036854775808ULL;
	total = 0;
	signal = 1;
	if (!status)
		return (0);
	while ((*status >= '\t' && *status <= '\r') || *status == ' ')
		status++;
	if (*status == '-' || *status == '+')
		if (*status++ == '-')
			signal *= -1;
	if (ft_strlen(status) > 19)
		return (0);
	while (ft_isdigit(*status) && total < max_lli)
		total = total * 10 + (*status++ - '0');
	if (total > max_lli)
		return (0);
	if (total == max_lli && signal == 1)
		return (0);
	return (1);
}

int	is_numeric_argument(char *str)
{
	int	space_flag;

	if (!str)
		return (0);
	space_flag = 0;
	while (*str && *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			if (*str == ' ')
				space_flag++;
			else
				return (0);
		}
		else
			if (space_flag && ft_isdigit(*str))
				return (0);
		str++;
	}
	return (1);
}

void	exit_ultra_safe(t_shell *shell)
{
	free_before_safely_exit(shell);
	exit_safely(shell, 1);
}

void	free_and_exit_builtin(t_shell *shell, t_node *node)
{
	free_process_data(shell);
	builtin_exit(shell, node);
}
