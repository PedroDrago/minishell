#include "../includes/minishell.h"

t_pid_node	*create_pid_node(pid_t pid)
{
	t_pid_node	*pid_node;

	pid_node = (t_pid_node *)malloc(sizeof(t_pid_node));
	if (!pid_node)
		return (NULL);
	pid_node->pid = pid;
	pid_node->next = NULL;
	return (pid_node);
}

void	append_pid_node(t_pid_list *list, t_pid_node *node)
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

t_pid_list	*create_pid_list(void)
{
	t_pid_list	*list;

	list = (t_pid_list *)malloc(sizeof(t_pid_list));
	if (!list)
		return (NULL);
	list->tail = NULL;
	list->head = NULL;
	return (list);
}
