#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char *substr2(char *str, int start, int end) //NOTE: Exclusive
{
	char *substr;
	int i;

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

void	do_split(char *str, char **splited)
{
	int end;
	int start;
	int	inside_quotes;

	end = 0;
	start = 0;
	inside_quotes = 0;
	while(str[end])
	{
		if ((str[end] == '\'' || str[end] == '\"') && str[end + 1] != '\\')
			inside_quotes = !inside_quotes;
		if (str[end] != ' ' && (str[end + 1] == ' ' || str[end + 1] == '\0'))
		{
			if (!inside_quotes)
			{
				*splited++ = substr2(str, start, end);
				while (str[++end] == ' ')
					;
				start = end;
			}
			else
				end++;
		}
		else
			end++;
	}
	*splited = NULL;
}

int	count_split(char *str)
{
	int end;
	int start;
	int	inside_quotes;
	int	count;

	end = 0;
	start = 0;
	inside_quotes = 0;
	count = 0;
	while(str[end])
	{
		if ((str[end] == '\'' || str[end] == '\"') && str[end + 1] != '\\')
			inside_quotes = !inside_quotes;
		if (str[end] != ' ' && (str[end + 1] == ' ' || str[end + 1] == '\0'))
		{
			if (!inside_quotes)
			{
				count++;
				while (str[++end] == ' ')
					;
				start = end;
			}
			else
				end++;
		}
		else
			end++;
	}
	(void) start;
	return (count);
}

char	**split_keep(char *str)
{
	char	**splited;
	char	*trimmed;

	trimmed = ft_strtrim(str, " ");
	splited = malloc(sizeof(char *) * (count_split(trimmed) + 1));
	if (!splited)
		return (NULL);
	do_split(trimmed, splited);
	print_split(splited);
	return (splited);
}
