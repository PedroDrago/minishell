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
		return (NULL);
	free (str);
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
		node->command = *splited;
		splited = parse_arguments(splited, node);
		if (!splited)
			return (FALSE);
		node->token = *splited;
		append_node(list, node);
		if (!(*splited++))
			return (TRUE);
	}
	return (TRUE);
}

t_list	*generate_list(char *prompt)
{
	char	**splited;
	t_list	*list;

	list = create_list();
	splited = ft_split(prompt, ' ');
	if (!splited || !list)
		return (NULL);
	fill_list(splited, list);
	return (list);
}
