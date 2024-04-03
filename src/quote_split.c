#include "../includes/minishell.h"
#include <readline/readline.h>
#include <stdio.h>

int	get_next_quote(char *str, int start, char quote)
{

	while(str[start++])
		if (str[start] == quote)
			return (start);
	return (start);
}

int	get_next_end(char *str, int start)
{
	while(str[start])
	{
		if (str[start + 1] == '\'' || str[start + 1] == '\"')
			return (start);
		start++;
	}
	return (start);
}
void	do_quote_split(char *str, char **splited)
{
	int	start;
	int	end;
	start = 0;
	end = 0;
	while(str[end])
	{
		if (str[end] == '\'')
		{
			end = get_next_quote(str, end, '\'');
			// printf("Single split from %i to %i\n", start, end);
			*splited++ = command_split_substr(str, start, end);
			if (!str[end])
				break ;
			start = ++end;
			if (!str[end])
				break ;
		}
		else if (str[end] == '\"')
		{
			end = get_next_quote(str, end, '\"');
			// printf("Double split from %i to %i\n", start, end);
			*splited++ = command_split_substr(str, start, end);
			if (!str[end])
				break ;
			start = ++end;
			if (!str[end])
				break ;
		}
		else
		{
			end = get_next_end(str, end);
			// printf("Normal split from %i to %i\n", start, end);
			*splited++ = command_split_substr(str, start, end);
			if (!str[end])
				break ;
			start = ++end;
			if (!str[end])
				break ;
		}
	}
}

char	**quote_split(char *str)
{
	char	**splited;

	splited = malloc(sizeof(char *) * 50);
	if (!splited)
		return (NULL);
	do_quote_split(str, splited);
	return (splited);
}

// int main(int argc, char *argv[])
// {
// 	while (1)
// 	{
// 		char **splited = quote_split(readline("$ "));
// 		int i = 0;
// 		while (splited[i])
// 		{
// 			printf("!%s!", splited[i++]);
// 		}
// 			printf("\n");
// 	}
// 	return 0;
// }
