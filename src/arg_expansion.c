/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:29 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:37:42 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	resolve_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	else if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
}

char	*get_expanded_arg(char *arg, t_shell *shell)
{
	t_env	*node;
	char	*value;

	if (!is_valid_arg_char(arg[1]))
		return (dup_value(arg));
	if (arg[1] == '?')
	{
		node = get_env_node(shell->env, "?");
		if (!node || !node->value)
			return (free(arg), ft_strdup(""));
		value = ft_strjoin(get_env_node(shell->env, "?")->value,
				&arg[2], O_NONE);
		return (free(arg), value);
	}
	node = get_env_node(shell->env, &arg[1]);
	if (!node || !node->value)
		return (free(arg), ft_strdup(""));
	return (free(arg), ft_strdup(node->value));
}

char	**expand_split(char **splited, t_shell *shell)
{
	int	i;
	int	j;
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	i = -1;
	while (splited[++i])
	{
		j = 0;
		while (splited[i][j])
		{
			resolve_quotes(splited[i][j], &in_single_quote, &in_double_quote);
			if (splited[i][j] == '$' && !in_single_quote)
			{
				splited[i] = get_expanded_arg(splited[i], shell);
				if (!splited[i])
					return (NULL);
				break ;
			}
			j++;
		}
	}
	return (splited);
}

void	expand_node_arguments(t_node *current, t_shell *shell)
{
	int		i;
	char	**splited;

	i = 0;
	while (current->args[i])
	{
		splited = expand_split(ft_split_charset_mod(current->args[i],
					"$\"\' ;!@#%^&*()[]{}`~|<>:.,/+=-_\t\a\b\n\v\f\r"), shell);
		if (!splited)
			return ;
		free(current->args[i]);
		current->args[i] = split_join(splited);
		free_split(splited);
		i++;
	}
}

void	expand_arguments(t_list *list, t_shell *shell)
{
	t_node	*current;

	current = list->head;
	while (current)
	{
		expand_node_arguments(current, shell);
		current = current->next;
	}
}
