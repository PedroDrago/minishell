#include "../includes/minishell.h"
#include <readline/readline.h>
#include <stdio.h>

int	valid_quotes(char *prompt)
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
		return (write(2, "Minishell: Unclosed quotes\n", 27), FALSE);
	return (TRUE);
}
