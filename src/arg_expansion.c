/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:45:34 by rafaelro          #+#    #+#             */
/*   Updated: 2024/03/08 05:14:58 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

// void	free_split(char **splited)
// {
// 	int	count;
//
// 	count = -1;
// 	while (splited[++count])
// 		free(splited[count]);
// 	free(splited);
// }

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
	return (splited);
}

char	**ft_split_charset_mod(char *str, char *charset)
{
	char	**splited;
	// int		i;
	// int		j;
	// int		k;

	// i = 0;
	// j = -1;
	// k = 0;
	splited = (char **)malloc(8 * charset_split_count(str, charset) + 1);
	if (!splited)
		return (NULL);
	split_loop(splited, str, charset);
	return (splited);
}

char *get_expanded_arg(char	**splited_arg, t_shell *shell)
{
	int	i;
	char *expanded_arg;
	char *parsed_arg;
	char *joined;
	t_env *node ;
	

	i = 0;
	joined = ft_calloc(1, 1);
	expanded_arg = "";
	while (splited_arg[i])
	{
		if (splited_arg[i][0] == '$')
		{
			parsed_arg = ft_strtrim(splited_arg[i],"\"$"); // FIX: this is fucked up about single quotes, and only adding it to the trim may fuck up arguments that have '" at the end
			node = get_env_node(shell->env, parsed_arg);
			if (node)
				expanded_arg = node->value;
			free(splited_arg[i]);
			free(parsed_arg);
			splited_arg[i] = ft_strdup(expanded_arg);
		}
		i++;
	}
	i = 1; // NOTE: starts at 1 to remove quote
	free(splited_arg[0]);
	while (splited_arg[i])
	{
		joined = ft_strjoin(joined, splited_arg[i], O_BOTH);
		i++;
	}
	return (joined);
}

void	expand_node_arguments(t_node *current_node, t_shell *shell)
{
	int	i;
	char *tmp;
	char **splited_arg;

	i = 0;
	while (current_node->args && current_node->args[i])
	{
		splited_arg = ft_split_charset_mod(current_node->args[i], " $");
		if (splited_arg[0][0] != '\'')
		{
			tmp = current_node->args[i];
			current_node->args[i] = get_expanded_arg(splited_arg, shell);
			free (tmp);
		}
		else
		{
			// TODO:remove simple quotes (trimm?) from argument.
			current_node->args[i] = ft_strtrim(current_node->args[i], "\'");
		}
		i++;
		free(splited_arg);
	}
}

void expand_arguments(t_list *list, t_shell *shell)
{
	t_node	*current_node;

	current_node = list->head;
	while (current_node)
	{
		expand_node_arguments(current_node, shell);
		current_node = current_node->next;
	}
}
