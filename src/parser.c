#include "../includes/minishell.h"
#include <stdio.h>

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

char	**parse_arguments(char **splited, t_node *node)
{
	char	*str;

	str = ft_calloc(1, 1);
	while (!is_token(*splited))
	{
		str = ft_strjoin(str, " ", O_ONE);
		if (!str)
			return (NULL);
		str = ft_strjoin(str, *splited, O_ONE);
		if (!str)
			return (NULL);
		splited++;
	}
	node->args = ft_split(str, ' ');
	if (!node->args)
		return (free(str), NULL);
	return (free(str), splited);
}

int	fill_list(char **splited, t_list *list)
{
	t_node	*node;

	while (*splited)
	{
		node = create_node();
		if (!node)
			return (FALSE);
		node->command = ft_strdup(*splited);
		splited = parse_arguments(splited, node);
		if (!splited)
			return (FALSE);
		if (!(*splited))
			node->token = NULL;
		else
			node->token = ft_strdup(*splited);
		append_node(list, node);
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
	if (!fill_list(splited, list))
		return (free_split(splited), free_list(list), NULL);
	free_split(splited);
	expand_arguments(list, shell);
	return (list);
}
