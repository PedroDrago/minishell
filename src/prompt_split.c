#include "../includes/minishell.h"

char	*prompt_split_substr(char *str, int start, int end)
{
	int		i;
	char	*substr;

	substr = malloc(sizeof(char) * (end - start + 2 - count_backslash(str,
					start, end)));
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

void	do_prompt_split(char *str, char **splited)
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
		if (str[end] == '|' && !in_single_quotes && !in_double_quotes)
		{
			*splited++ = prompt_split_substr(str, start, end);
			if (str[end + 1] == '\0')
			{
				*splited = NULL;
				return ;
			}
			start = ++end;
		}
		else
			end++;
	}
	*splited++ = prompt_split_substr(str, start, end);
	*splited = NULL;
}

//Splits the actual prompt into basic commands (split by pipe)
//splits `ls | grep a > test.txt < test2.txt | wc`
//into `!ls |!! grep a > test.txt < test2.txt |!! wc!`
char	**prompt_split(char *str)
{
	char	**splited;
	char	*trimmed;

	trimmed = ft_strtrim(str, " ");
	if (!trimmed)
		return (NULL);
	splited = malloc(sizeof(char *) * (count_split(trimmed) + 1));
	if (!splited)
		return (free(trimmed), NULL);
	do_prompt_split(trimmed, splited);
	free(trimmed);
	return (splited);
}
