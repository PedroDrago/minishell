#include "../includes/minishell.h"

int	get_end_q(char *str, char quote, int start)
{
	while (str[start])
	{
		if (str[start] == quote && (str[start + 1] == ' ' || str[start
					+ 1] == '\0'))
			return (start);
		start++;
	}
	return (start);
}

int	get_substr_quote_len(char *str, int start, int end, char quote)
{
	int	ignored;

	ignored = 0;
	start++;
	while (start < end)
	{
		if (str[start] == quote)
			ignored++;
		start++;
	}
	return (end - start + 1 - ignored);
}

char	*substr_q(char *str, int start, int end, char quote)
{
	char	*substr;
	int		i;

	substr = malloc(sizeof(char) * get_substr_quote_len(str, start, end, quote)
			+ 1);
	if (!substr)
		return (NULL);
	i = 0;
	substr[i++] = str[start++];
	while (start < end)
	{
		while (str[start] == quote && start < end)
			start++;
		substr[i++] = str[start++];
	}
	substr[i++] = str[start];
	substr[i] = '\0';
	return (substr);
}
