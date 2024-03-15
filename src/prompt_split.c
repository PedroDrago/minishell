#include "../includes/minishell.h"
#include <inttypes.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int	get_end(char *str, int start)
{
	while (str[start])
	{
		if (str[start] != ' ' && (str[start + 1] == ' ' || str[start
					+ 1] == '\0'))
			return (start);
		start++;
	}
	return (start);
}

char	*substr(char *str, int start, int end)
{
	char	*substr;
	int		i;

	substr = malloc(sizeof(char) * end - start + 2);
	if (!substr)
		return (NULL);
	i = 0;
	while (start <= end)
		substr[i++] = str[start++];
	substr[i] = '\0';
	return (substr);
}

void	do_split(char *str, char **splited)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			*splited++ = substr_q(str, i, get_end_q(str, '\"', i), '\"');
			i = get_end_q(str, '\"', i) + 1;
		}
		else if (str[i] == '\'')
		{
			*splited++ = substr_q(str, i, get_end_q(str, '\"', i), '\'');
			i = get_end_q(str, '\"', i) + 1;
		}
		else
		{
			*splited++ = substr(str, i, get_end(str, i));
			i = get_end(str, i) + 1;
		}
		while (str[i] == ' ')
			i++;
	}
	*splited = NULL;
}

int	prompt_split_count(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		count++;
		if (str[i] == '\"')
			i = get_end_q(str, '\"', i) + 1;
		else if (str[i] == '\'')
			i = get_end_q(str, '\'', i) + 1;
		else
			i = get_end(str, i) + 1;
		while (str[i] == ' ')
			i++;
	}
	return (count);
}

char	**prompt_split(char *s)
{
	char	**splited;
	char	*str;

	str = ft_strtrim(s, " ");
	if (!str)
		return (NULL);
	splited = malloc(sizeof(char *) * prompt_split_count(str) + 1);
	if (!splited)
		return (free(str), NULL);
	do_split(str, splited);
	return (free(str), splited);
}
