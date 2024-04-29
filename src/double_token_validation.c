/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_token_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:14:21 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/26 21:15:33 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	is_token_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	print_double_token_error(char c)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token `", 2),
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	return (FALSE);
}

void	init_flags(t_validation *flags, int *count)
{
	flags->token_last = 0;
	flags->in_double_quotes = 0;
	flags->in_single_quotes = 0;
	*count = -1;
}

int	not_in_quotes(t_validation *flags)
{
	if (flags->in_single_quotes || flags->in_double_quotes)
		return (FALSE);
	return (TRUE);
}

int	validate_double_tokens(char *prompt)
{
	int				i;
	t_validation	flags;

	init_flags(&flags, &i);
	while (prompt[++i])
	{
		resolve_quotes(prompt[i], &flags.in_single_quotes,
			&flags.in_double_quotes);
		if (is_token_char(prompt[i]) && not_in_quotes(&flags))
		{
			if (flags.token_last)
				return (print_double_token_error(prompt[i]));
			if (prompt[i] == '<')
				if (prompt[i + 1] == '<')
					i++;
			if (prompt[i] == '>')
				if (prompt[i + 1] == '>')
					i++;
			flags.token_last = 1;
		}
		else if (not_in_quotes(&flags))
			if (prompt[i] != ' ')
				flags.token_last = 0;
	}
	return (TRUE);
}
