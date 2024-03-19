
#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	is_charset(char c, char *charset)
{
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}

int	charset_split_count(char *str, char *charset)
{
	int	count;

	count = 1;
	while (*str)
		if (is_charset(*str++, charset))
			count++;
	return (count);
}

char	*ft_strndup(char *str, int n)
{
	char	*new_str;
	int		i;

	if (!str || n <= 0)
		return (NULL);
	new_str = (char *)malloc(n + 1);
	i = -1;
	while (str[++i] && n--)
		new_str[i] = str[i];
	new_str[i] = '\0';
	return (new_str);
}

char	**split_loop(char **splited, char *str, char *charset)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = i;
	k = j;
	while (str[i + ++j])
	{
		if (is_charset(str[i + j], charset) && j > 0)
		{
			splited[k] = ft_strndup(&str[i], j);
			if (!splited[k++])
				return (free_split(splited), NULL);
			i = i + j;
			j = 0;
		}
		if (!str[i + j + 1])
			splited[k] = ft_strndup(&str[i], j + 1);
	}
	if (!splited[k++])
		return (free_split(splited), NULL);
	splited[k] = NULL;
	print_split(splited);
	return (splited);
}

char	**ft_split_charset_mod(char *str, char *charset)
{
	char	**splited;

	if (ft_strlen(str) == 1)
		return (ft_split(str, '\0'));
	splited = (char **)malloc(sizeof(char *) * (charset_split_count(str, charset) + 1));
	if (!splited)
		return (NULL);
	split_loop(splited, str, charset);
	return (splited);
}

int	is_valid_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

char *get_expanded_arg(char *arg, t_shell *shell)
{
	t_env *node;

	if (!is_valid_char(arg[1]))
		if (arg[2])
			return (ft_strdup(&arg[2]));
	node = get_env_node(shell->env, &arg[1]);
	if (!node || !node->value)
		return (ft_strdup(""));
	free(arg);
	return (ft_strdup(node->value));
}


void	resolve_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	else if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
}


char **expand_split(char **splited, t_shell *shell)
{
	int	i;
	int	j;
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	i = -1;
	while(splited[++i])
	{
		j = 0;
		while(splited[i][j])
		{
			resolve_quotes(splited[i][j], &in_single_quote, &in_double_quote);
			if (splited[i][j] == '$' && !in_single_quote)
			{
				splited[i] = get_expanded_arg(splited[i], shell);
				if (!splited[i])
					return (NULL); // WARN: Malloc error
				break ;
			}
			j++;
		}
	}
	return (splited);
}

void	init_vars(int *j, int *z, int *single_q, int *double_q)
{
	*j = 0;
	*z = 0;
	*single_q = 0;
	*double_q = 0;
}

int	split_str_len(char **splited)
{
	int    i;
	int    j;
	int    z;
	int	inside_single;
	int	inside_double;

	i = -1;
	init_vars(&j, &z, &inside_single, &inside_double);
	while(splited && splited[++i])
	{
		j = 0;
		while (splited[i][j])
		{
			if (splited[i][j] && splited[i][j] == '\'' && j > 0 && splited[i][j - 1] != '\\' && !inside_double)
			{
					j++;
			}
			if (splited[i][j] && splited[i][j] == '\"' && j > 0 && splited[i][j - 1] != '\\' && !inside_single)
			{
					j++;
			}
			if (!splited[i][j])
			{
				break ;
			}
			j++;
			z++;
		}
	}
	return (z);
}

void split_join_loop(char **splited, char *join, int z)
{
	int	inside_double;
	int	inside_single;
	int	i; 
	int	j;

	inside_double = 0;
	inside_single = 0;
	i = -1;
	while(splited[++i])
	{
		j = 0;
		while (splited[i] && splited[i][j])
		{
			if (splited[i][j] == '\'' && (j == 0 || splited[i][j - 1] != '\\'))
				if (!inside_double && ++j)
					inside_single = !inside_single;
			if (splited[i][j] == '\"' && (j == 0 || splited[i][j - 1] != '\\'))
				if (!inside_single && ++j)
					inside_double = !inside_double;
			if (!splited[i][j])
				break ;
			join[z++] = splited[i][j++];
		}
	}
	join[z] = '\0';
}

char *split_join(char **splited)
{
	char    *join;

	join = malloc(sizeof(char) * (split_str_len(splited) + 1));
	if (!join)
		return (NULL);
	split_join_loop(splited, join, 0);
	return (join);
}


void	expand_node_arguments(t_node *current, t_shell *shell)
{
	int	i;
	char **splited;

	i = 0;
	// print_split(current->args);
	while (current->args[i])
	{
		splited = expand_split(ft_split_charset_mod(current->args[i], "$\"\'"), shell);
		if (!splited)
			return ; // WARN: Malloc error
		free(current->args[i]);
		current->args[i] = split_join(splited);
		free_split(splited);
		i++;
	}
}

void	expand_arguments(t_list *list, t_shell *shell)
{
	t_node *current;

	current = list->head;
	while (current)
	{
		expand_node_arguments(current, shell);
		current = current->next;
	}
}
