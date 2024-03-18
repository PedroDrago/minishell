#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char *test_substr(char *str, int start, int end) //NOTE: Exclusive
{
	char *substr;
	int i;

	substr = malloc(sizeof(char) * end - start + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (start < end)
	{
		substr[i] = str[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
int	is_argument_character(char c)
{
	return (ft_isalnum(c) || c == '_');

}
int	get_arg_end(char *str, int start)
{
	if (ft_isdigit(str[start + 1]) || !is_argument_character(str[start + 1])) // NOTE: Args cant start with numbers, parsing behaviour is if it start with number automatically evalautes it to nothing, no characters at all "$2PATH" -> PATH
		return (start);
	start++; // NOTE: skip $
	while(is_argument_character(str[start]))
		start++;
	return (start);
}

int	count_split(char *str)
{
	int	count;
	int i;
	int j;

	count = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (i != 0 && str[j] != '$')
				count++;
			if (i == get_arg_end(str, i))
				i += 2;
			count++;
			j = get_arg_end(str, i);
			if (!str[j])
				return (count);
		}
		i++;
	}
	count++;
	return (count);
}

int	do_test_split(char *str, char **splited) //NOTE: decide behaviour for empty str. split with NULL on 0 index or split with empty string on 0 index?
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (i != 0 && str[j] != '$')
			{
				// printf("Normal from %i to %i\n", j, i);
				*splited = test_substr(str, j, i);
				if (!(*splited++))
					return (0);
			}
			if (i == get_arg_end(str, i))
				i += 2;
			// printf("Args from %i to %i\n", i, get_arg_end(str, i));
			*splited = test_substr(str, i, get_arg_end(str, i));
			if (!(*splited++))
				return (0);
			j = get_arg_end(str, i);
			if (!str[j])
			{
				*splited = NULL;
				return (1);
			}
		}
		i++;
	}
	// printf("Normal from %i to %i\n", j, i);
	*splited = test_substr(str, j, i);
	if (!(*splited))
		return (0);
	splited++;
	*splited = NULL;
	return (1);
}

char **no_arg_split(char *str)
{
	char **splited;

	splited = malloc(sizeof(char *) * 2);
	if (!splited)
		return (NULL);
	splited[0] = ft_strdup(str);
	if (!splited[0])
		return (NULL);
	splited[1] = NULL;
	return (splited);
}

char	**test_split(char *str)
{
	char **splited;

	if (!ft_strchr(str, '$'))
		return (no_arg_split(str));
	splited = malloc(sizeof(char *) * count_split(str));
	if (!splited)
		return (NULL);
	if (!do_test_split(str, splited))
		return (free_split(splited), NULL);
	return (splited);
}
//
// int main(void)
// {
//
// 	while (1)
// 	{
// 		char **splited = test_split(readline(("$ ")));
// 		print_split(splited);
// 	}
// 	return 0;
// }
