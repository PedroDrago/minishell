#include "../includes/minishell.h"

int	is_splitable(char *str, int end, int in_single_quotes, int in_double_quotes)
{
	return (str[end] != ' ' && (str[end + 1] == ' ' || str[end + 1] == '\0')
		&& (!in_single_quotes && !in_double_quotes));
}

int	count_command_split(char *str)
{
	int	end;
	int	count;
	int	in_double_quotes;
	int	in_single_quotes;

	end = 0;
	count = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	while (str[end])
	{
		resolve_quotes(str[end], &in_single_quotes, &in_double_quotes);
		if (is_splitable(str, end, in_single_quotes, in_double_quotes))
		{
			count++;
			while (str[++end] && str[end] == ' ')
				;
			if (!str[end])
				break ;
		}
		else
			end++;
	}
	return (count);
}
