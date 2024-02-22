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

int	parse_arguments(char **splited, int *i, t_node *node)
{
	char	*str;

	str = ft_calloc(1, 1);
	while (!is_token(splited[*i]))
	{
		str = ft_strjoin(str, " ", O_ONE);
		if (!str)
			return (FALSE);
		str = ft_strjoin(str, splited[*i], O_ONE);
		if (!str)
			return (FALSE);
		(*i)++;
	}
	node->args = ft_split(str, ' ');
	if (!node->args)
		return (FALSE);
	free (str);
	return (TRUE);
}

int	fill_list(char **splited, t_list *list)
{
	int		i;
	t_node	*node;

	i = 0;
	while (splited[i])
	{
		node = create_node();
		if (!node)
			return (FALSE);
		node->command = splited[i++];
		if (!parse_arguments(splited, &i, node))
			return (FALSE);
		node->token = splited[i];
		append_node(list, node);
		if (!splited[i++])
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

int	evaluate(char *prompt, t_shell *shell)
{
	t_list	*prompt_list;

	prompt_list = generate_list(prompt);
	if (!prompt_list)
		return (FALSE);
	print_list(prompt_list);
	(void) shell;
	return (TRUE);
}
