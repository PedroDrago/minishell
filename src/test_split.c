#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	count_backslash(char *str, int start, int end)
{
	int	count;

	count = 0;
	while (start <= end)
	{
		if (str[start] == '\\')
			count++;
		start++;
	}
	return (count);
}

char *substr2(char *str, int start, int end) //NOTE: Exclusive
{
	char *substr;
	int i;

	substr = malloc(sizeof(char) * (end - start + 2 - count_backslash(str, start, end)));
	if (!substr)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		if (str[start] != '\\')
		{
			substr[i] = str[start];
			i++;
		}
		start++;
	}
	substr[i] = '\0';
	return (substr);
}


int	count_split(char *str)
{
	int end;
	int	in_double_quotes;
	int	in_single_quotes;
	int	count;

	end = 0;
	count = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	while(str[end])
	{
		if (str[end] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		if (str[end] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if (str[end] != ' ' && (str[end + 1] == ' ' || str[end + 1] == '\0') && (!in_single_quotes && !in_double_quotes))
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

void	do_split(char *str, char **splited)
{
	int end;
	int start;
	int	in_double_quotes;
	int	in_single_quotes;

	end = 0;
	start = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	while(str[end])
	{
		if (str[end] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		if (str[end] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if (str[end] != ' ' && (str[end + 1] == ' ' || str[end + 1] == '\0') && (!in_single_quotes && !in_double_quotes))
		{
			*splited++ = substr2(str, start, end);
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

char	**split_keep(char *str)
{
	char	**splited;
	char	*trimmed;

	trimmed = ft_strtrim(str, " ");
	if (!trimmed)
		return (NULL);
	splited = malloc(sizeof(char *) * (count_split(trimmed) + 1));
	if (!splited)
		return (free(trimmed), NULL);
	do_split(trimmed, splited);
	free(trimmed);
	return (splited);
}

// int main()
// {
// 	
// 	while (1)
// 	{
// 		char **splited = split_keep(readline("$ "));
// 		print_split(splited);
// 	}
// 	return 0;
// }
