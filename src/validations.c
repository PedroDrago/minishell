#include "../includes/minishell.h"

int	valid_prompt(char *prompt)
{
	if (!valid_characters(prompt))
		return (FALSE);
	return (TRUE);
}

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
