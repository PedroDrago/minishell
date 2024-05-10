/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:19:02 by pdrago            #+#    #+#             */
/*   Updated: 2024/05/07 16:38:16 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_quotes(char *prompt)
{
	int	single_quotes;
	int	double_quotes;
	int	count;

	single_quotes = 0;
	double_quotes = 0;
	count = -1;
	while (prompt[++count])
	{
		if (prompt[count] == '\'')
		{
			single_quotes++;
			if (double_quotes % 2 != 0)
				single_quotes = 0;
		}
		else if (prompt[count] == '\"')
		{
			double_quotes++;
			if (single_quotes % 2 != 0)
				double_quotes = 0;
		}
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (ft_putstr_fd("Minishell: Unclosed quotes\n", 2), FALSE);
	return (TRUE);
}

int	validate_edge_tokens(char *str)
{
	while (*str)
	{
		if (ft_strchr("|<>", *str))
			break ;
		if (!ft_strchr("|<> \t\a\b\n\v\f\r", *str))
			return (TRUE);
		str++;
	}
	ft_putstr_fd("[EDGE TOKENS]", 2);
	if (!ft_strncmp(str, "||", 2))
		ft_putstr_fd("Minishell: syntax error near unexpected token `||'\n", 2);
	else if (!ft_strncmp(str, "|", 1))
		ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n", 2);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token\
	       `newline'\n", 2);
	return (FALSE);
}

int	validate_unresolved_tokens(char *prompt)
{
	char	last;

	last = prompt[ft_strlen(prompt) - 1];
	if (is_token_char(last))
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2),
		ft_putchar_fd(last, 2);
		ft_putstr_fd("'\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

int	validate_tokens(char *prompt)
{
	if (!validate_unresolved_tokens(prompt))
		return (FALSE);
	if (!validate_edge_tokens(prompt))
		return (FALSE);
	if (!validate_double_tokens(prompt))
		return (FALSE);
	return (TRUE);
}

int	validate_prompt(char *prompt, t_shell *shell)
{
	if (!prompt || !ft_strlen(prompt))
		return (FALSE);
	if (!validate_quotes(prompt) || !validate_tokens(prompt))
	{
		set_exit_status(2, shell);
		return (FALSE);
	}
	return (TRUE);
}
