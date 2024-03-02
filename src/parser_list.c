#include "../includes/minishell.h"

t_node	*create_node(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->token = NULL;
	node->args = NULL;
	node->command = NULL;
	node->next = NULL;
	return (node);
}

void	append_node(t_list *list, t_node *node)
{
	if (!list || !node)
		return ;
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
		return ;
	}
	list->tail->next = node;
	list->tail = node;
}

t_list	*create_list(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->tail = NULL;
	list->head = NULL;
	return (list);
}

void	free_list(t_list *list)
{
	t_node	*tmp;

	if (!list)
		return ;
	tmp = list->head;
	while (tmp)
	{
		if (tmp->args)
			free_split(tmp->args);
		if (tmp->command)
			free(tmp->command);
		if (tmp->token)
			free(tmp->token);
		tmp = tmp->next;
	}
	free(list);
}
