/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:25 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:38:25 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_token(char *item)
{
	if (!item)
		return (TRUE);
	else if (!ft_strncmp(item, "|", 2))
		return (TRUE);
	else if (!ft_strncmp(item, "<", 2))
		return (TRUE);
	else if (!ft_strncmp(item, "<<", 3))
		return (TRUE);
	else if (!ft_strncmp(item, ">", 2))
		return (TRUE);
	else if (!ft_strncmp(item, ">>", 3))
		return (TRUE);
	return (FALSE);
}

int	count_arg_split(char **splited)
{
	int	count;

	count = 0;
	while (!is_token(splited[count]))
		count++;
	return (count);
}

char	**parse_arguments(char **splited, t_node *node)
{
	int	i;

	i = 0;
	node->args = malloc(sizeof(char *) * (count_arg_split(splited) + 1));
	if (!node->args)
		return (NULL);
	while (!is_token(*splited))
		node->args[i++] = ft_strdup(*splited++);
	node->args[i] = NULL;
	return (splited);
}

int	fill_list(char **splited, t_list *list)
{
	t_node	*node;

	while (*splited)
	{
		node = create_node();
		if (!node)
			return (FALSE);
		if (!is_token(*splited))
		{
			node->command = ft_strdup(*splited);
			splited = parse_arguments(splited, node);
			if (!splited)
				return (FALSE);
			if (!(*splited))
				node->token = NULL;
			else
				node->token = ft_strdup(*splited);
			append_node(list, node);
		}
		if (!(*splited++))
			return (TRUE);
	}
	return (TRUE);
}

t_list	*generate_list(char *prompt, t_shell *shell)
{
	char	**splited;
	t_list	*list;

	list = create_list();
	if (!list)
		return (NULL);
	splited = prompt_split(prompt);
	if (!splited)
		return (NULL);
	if (has_invalid_characters(splited))
		return (free_split(splited), write(2,
				"Minishell: Invalid Characters (; or \\) \n", 40), NULL); //FIX: Trocar write por ft_pustr_fd
	if (!fill_list(splited, list))
		return (free_split(splited), free_list(list), NULL);
	free_split(splited);
	expand_arguments(list, shell);
	return (list);
}
