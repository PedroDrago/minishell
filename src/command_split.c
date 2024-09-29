#include "../includes/minishell.h"

char	*command_split_substr(char *str, int start, int end)
{
	int		i;
	char	*substr;

	substr = malloc(sizeof(char) * (end - start + 2));
	if (!substr)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		substr[i] = str[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}

void	do_command_split(char *str, char **splited)
{
	int	end;
	int	start;
	int	in_double_quotes;
	int	in_single_quotes;

	end = 0;
	start = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	while (str[end])
	{
		resolve_quotes(str[end], &in_single_quotes, &in_double_quotes);
		if (is_splitable(str, end, in_single_quotes, in_double_quotes))
		{
			*splited++ = command_split_substr(str, start, end);
			while (str[++end] && str[end] == ' ')
				;
			start = end;
			if (!str[end])
				break ;
		}
		else
			end++;
	}
	*splited = NULL;
}

char	**command_split(char *str)
{
	char	**splited;
	char	*trimmed;

	trimmed = ft_strtrim(str, " ");
	if (!trimmed)
		return (NULL);
	splited = malloc(sizeof(char *) * (count_command_split(trimmed) + 1));
	if (!splited)
		return (free(trimmed), NULL);
	do_command_split(trimmed, splited);
	free(trimmed);
	return (splited);
}
