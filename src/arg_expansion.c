/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:45:34 by rafaelro          #+#    #+#             */
/*   Updated: 2024/03/16 16:15:56 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	if (ft_strlen(str) == 1)
		return (ft_split(str, '\''));
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
	if (splited[0][0] == '\"' || splited[0][0] == '\'')
		len -= 2;
	return (len);
}

char *split_join(char **splited)
{
	char	*join;
	int	i;
	int	j;
	int	z;
	int	quote;

	join = malloc(sizeof(char) * (split_str_len(splited) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	z = 0;
	quote = 0;
	if (splited[0][0] == '\"' || splited[0][0] == '\'')
	{
		quote = 1;
		if (splited[0][0] == '\"')
			quote = 2;
	}
	while(splited[i])
	{
		j = 0;
		while (splited[i][j])
		{
			if (((splited[i][j] == '\"' && quote == 2)
				|| (splited[i][j] == '\'' && quote == 1)) && ++j)
				continue;
			join[z] = splited[i][j];
			z++;
			j++;
		}
		i++;
	}
	join[z] = '\0';
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
		splited = ft_split_charset_mod(node->args[i], " $\"\'");
		j = 0;
		while (splited[j])
		{
			if (splited[0][0] != '\"' && splited[j][0] == '\'')
				break;
			if (splited[j][0] == '$')
			{
				env = get_env_node(shell->env, &splited[j][1]);
				if (env)
					value = ft_strdup(env->value);
				else
					value = ft_strdup("");
				splited[j] = value;
			}
			j++;
		}
		free(node->args[i]);
		node->args[i] = split_join(splited);
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
