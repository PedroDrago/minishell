#include "../includes/minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


# define DEBUG 0

int count_splits(char *str)
{
	int	count;
	int	splits;
	int	quote_count;

	count = 0;
	splits = 0;
	quote_count = 0;
	while (str[count])
	{
		if (str[count] == '\"')
		{
			quote_count++;
			while (str[count])
			{
				count++;
				if (str[count] == '\0')
					break ;
				while(str[count] != '\"')
					count++;
				quote_count++;
				if (quote_count % 2 == 0 && (str[count + 1] == ' ' || str[count + 1] == '\0'))
				{
					splits++;
					count++;
					quote_count = 0;
					break ;
				}
			}
			if (str[count] == '\0')
				return (splits);
		}
		if (str[count] == '\'')
		{
			quote_count++;
			while (str[count])
			{
				count++;
				if (str[count] == '\0')
					break ;
				while(str[count] != '\'')
					count++;
				quote_count++;
				if (quote_count % 2 == 0 && (str[count + 1] == ' ' || str[count + 1] == '\0'))
				{
					splits++;
					count++;
					quote_count = 0;
					break ;
				}
			}
			if (str[count] == '\0')
				return (splits);
		}
		else
			if (str[count] != ' ' && (str[count + 1] == ' ' || str[count + 1] == '\0'))
				splits++;
		count++;
	}
	return (splits);
}

int substr_len_quote(char *str, int start_i, int end_i, char quote)
{
	int	quotes;
	int	len;

	quotes = 0;
	len = end_i - start_i - 1;
	while (str && start_i++ < end_i)
	{
		if (str[start_i] == quote)
			quotes++;
		start_i++;
	}
	return (len - quotes + 2);
}

char *quote_substr(char *str, int start, int end, char quote)
{
	char	*substr;
	int	i;

	substr = ft_calloc(sizeof(char) , substr_len_quote(str, start, end, quote) + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		while (str[start] == quote && (i != 0 && start != end)) // NOTE: Skip quote if not first or last quotes
			start++;
		substr[i++] = str[start++];
	}
	substr[i] = '\0';
	return (substr);
}

int	get_end_quote(char *str, int start, char quote)
{
	int quote_count;
	int	end;

	quote_count = 1;
	end = -1;
	while (str[start])
	{
		start++;
		if (str[start] == '\0')
			break ;
		while(str[start] != quote)
			start++;
		quote_count++;
		if (quote_count % 2 == 0 && (str[start + 1] == ' ' || str[start + 1] == '\0'))
		{
			end = start;
			break ;
		}
	}
	return (end);
}
int	get_end_space(char *str, int start)
{
	while (str[start])
	{
		if (str[start] != ' ' && (str[start + 1] == ' ' || str[start + 1] == '\0'))
			return (start);
		start++;
	}
	return (-1);
}

int	default_substr_len(char *str, int start, int end)
{
	int	quotes;

	quotes = 0;
	int	i;
	i = start;
	while (i <= end)
	{
		if (str[i] == '\"' || str[i] == '\'')
			quotes++;
		i++;
	}
	return (end - start - quotes);
}
char *default_substr(char *str, int start, int end)
{
	char	*substr;
	int	i;

	substr = ft_calloc(sizeof(char) , default_substr_len(str, start, end));
	if (!substr)
		return(NULL);
	i = 0;
	while(str[start] && start <= end)
	{
		while (str[start] == '\"' || str[start] == '\'')
			start++;
		substr[i] = str[start];
		i++;
		start++;
	}
	substr[++i] = '\0';
	return (substr);
}

void do_split(char *str, char **splited)
{
	int	start;
	int	end;
	char *hold;

	start = 0;
	while (str[start])
	{
		if (str[start] == '\"')
		{
			*splited = quote_substr(str, start, get_end_quote(str, start, '\"'), '\"');
			// printf("\nfrom %i to %i: |%s|", start, get_end_quote(str, start, '\"'), *splited);
			start = get_end_quote(str, start, '\"') + 1;
			// printf("---- start after: %i\n", start);
			// printf("--------------------\n");
			splited++;
		}
		else if (str[start] == '\'')
		{
			*splited = quote_substr(str, start, get_end_quote(str, start, '\''), '\'');
			start = get_end_quote(str, start, '\'') + 1;
			splited++;
		}
		else
		{
			*splited = default_substr(str, start, get_end_space(str, start));
			// printf("\nfrom %i to %i: |%s|", start, get_end_space(str, start), *splited);
			start = get_end_space(str, start) + 1;
			// printf("---- start after: %i\n", start);
			// printf("--------------------\n");
			splited++;
		}
		while (str[start] == ' ')
			start++;
		if (str[start] == '\0')
			break ;
	}
	*splited = NULL;
}

char **prompt_split(char *s)
{
	char **splited;

	char *str = ft_strtrim(s, " ");
	if (!str)
		return (NULL);
	splited = malloc(sizeof(char *) * count_splits(str) + 1);
	if (!splited)
		return(free(str), NULL);
	do_split(str, splited);
	return (splited);
}

int main(int argc, char *argv[]){


	while (1)
	{
		char **test = prompt_split(readline("$ "));
		int	count = 0;;

		while(test && test[count])
			printf("|%s|\n", test[count++]);
	}
}
