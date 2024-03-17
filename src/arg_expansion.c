/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:45:34 by rafaelro          #+#    #+#             */
/*   Updated: 2024/03/17 01:52:58 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (splited);
}

char	**ft_split_charset_mod(char *str, char *charset) // FIX: echo "tes                  te" -> este prompt vai sair como `tes te`, os espacos consecutivos estao sendo engolidos
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


int	split_str_len(char **splited)
{
	int len;
	int	i;

	if (!splited)
		return (0);
	len = 0;
	i = 0;
	while (splited[i])
	{
		len += ft_strlen(splited[i]);
		i++;
	}
	return (len);
}

char *remove_leading_quotes(char *str)
{
	char *new_str;
	int	len;
	int	i;
	int	j;

	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len - 1));
	if (!new_str)
		return (NULL);
	if (len == 2)
	{
		new_str[0] = '\0';
		return (new_str);
	}
	i = 1;
	j = 0;
	while (i < (len - 1))
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

char *split_join(char **splited)
{
	char	*join;
	int	i;
	int	j;
	int	z;

	join = malloc(sizeof(char) * (split_str_len(splited) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	z = 0;
	while(splited[i])
	{
		j = 0;
		while (splited[i][j])
		{
			join[z] = splited[i][j];
			z++;
			j++;
		}
		i++;
	}
	join[z] = '\0';
	if (join[0] == '\"' || join[0] == '\'')
		join = remove_leading_quotes(join);
	return (join);
}


void	expand_node_arguments(t_node *node, t_shell *shell)
{
	int	i;
	int	j;
	char	**splited;
	t_env	*env;
	char	*value;

	i = 0;
	while (node->args[i])
	{
		// printf("node->args[i]: %s\n", node->args[i]);
		splited = test_split(node->args[i]);
		// print_split(splited);
		if (!splited)
			return;
		if (!splited[0])
			continue;
		if (splited[0][0] != '\'')
		{
			j = 0;
			while (splited[j])
			{
				if (splited[j][0] == '$')
				{
					env = get_env_node(shell->env, &splited[j][1]);
					if (!env)
						value = ft_strdup("");
					else
						value = ft_strdup(env->value);
					free(splited[j]);
					splited[j] = value;
				}
				j++;
			}
		}
		free(node->args[i]);
		node->args[i] = split_join(splited);
		free(splited);
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
	// print_list(list);
}
