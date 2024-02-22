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

int	fill_list(char **splited, t_list *list, char *str)
{
	int		i;
	t_node	*node;

	i = 0;
	while (splited[i])
	{
		str = ft_calloc(1, 1);
		node = create_node();
		if (!node || ! str)
			return (FALSE);
		node->command = splited[i++];
		while (!is_token(splited[i]))
		{
			str = ft_strjoin(str, splited[i++], O_ONE);
			if (!str)
				return (FALSE);
		}
		node->args = ft_split(str, ' ');
		if (!node->args)
			return (FALSE);
		free (str);
		node->token = splited[i++];
		append_node(list, node);
	}
	return (TRUE);
}

t_list	*generate_list(char *prompt)
{
	char	**splited;
	char	*str;
	t_list	*list;

	list = create_list();
	splited = ft_split(prompt, ' ');
	if (!splited || !list || !splited)
		return (NULL);
	fill_list(splited, list, str);
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
