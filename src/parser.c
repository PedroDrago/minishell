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
		return (NULL);
	free(str);
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
		node->command = ft_strdup(*splited);
		splited = parse_arguments(splited, node);
		if (!splited)
			return (FALSE);
		if (!(*splited))        // NOTE: strdup da segfault se vc passa nulo, poderia 
					// alterar a funcao mas prefiro consultar voce @rafael antes pra ver o que acha então fiz um if/else pra lidar com isso por enquanto
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
		return (NULL); // free_list
	if (!fill_list(splited, list))
		return (free_split(splited), free_list(list), NULL);
	free_split(splited); // NOTE: antes nossos nodes tinham referencia pra memoria do split, isso é problematico para dar free nas coisas. Agora são copias, e splited é liberado assim que a função acaba
	expand_arguments(list, shell);
	return (list);       
}
