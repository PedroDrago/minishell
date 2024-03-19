#include "../includes/minishell.h"
#include <stdio.h>
#include <strings.h>

int	get_end_q(char *str, char quote, int start)
{
	int	index;

	index = start + 1;
	while (str[index])
	{
		if (quote == '\'' && str[index] == quote)
			return (index);
		else if (quote == '\"' && str[index] == quote && str[index - 1] != '\\')
			return (index);
		index++;
	}
	return (index);
}

int	get_substr_quote_len(char *str, int start, int end, char quote)
{
	int	ignored;
	int	index;

	ignored = 0;
	index = start + 1;
	while (index < end)
	{
		if (quote == '\"' && str[index] == quote && str[index - 1] != '\\')
			ignored ++;
		index++;
	}
	return (end - start + 1 - ignored);
}

char	*substr_q(char *str, int start, int end, char quote)
{
	char	*substr;
	int		i;

	substr = malloc(sizeof(char) * (get_substr_quote_len(str, start, end, quote) + 1));
	if (!substr)
		return (NULL);
	i = 0;
	substr[i++] = str[start++];
	while (start < end)
	{
		if (str[start] == '\\' && str[start + 1] == '\"')
			start++;
		substr[i++] = str[start++];
	}
	substr[i++] = str[start];
	substr[i] = '\0';
	return (substr);
}
