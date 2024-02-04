/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:29:05 by pdrago            #+#    #+#             */
/*   Updated: 2024/02/04 18:45:46 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_characters(char *prompt)
{
	int	single_quotes;
	int	double_quotes;
	int	count;

	single_quotes = 0;
	double_quotes = 0;
	count = 0;
	while (prompt[count])
	{
		if (prompt[count] == '\\' || prompt[count] == ';')
			return (FALSE);
		else if (prompt[count] == '\'')
			single_quotes++;
		else if (prompt[count] == '"')
			double_quotes++;
		count++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (FALSE);
	return (TRUE);
}

int	valid_prompt(char *prompt)
{
	if (!valid_characters(prompt))
		return (FALSE);
	return (TRUE);
}

int	main(void)
{
	char	*prompt;
	int		history_fd;

	history_fd = open("history", O_RDWR | O_APPEND | O_CREAT, 0777);
	while (TRUE)
	{
		prompt = readline("$ ");
		if (!register_command(prompt, history_fd)) 
			return (1);
		if (!valid_prompt(prompt))
		{
			write(2, "Minishell: Invalid Prompt\n", 26);
			continue;
		}
	}
}
