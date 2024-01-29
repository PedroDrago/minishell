/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:11:21 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:49:27 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	ft_free_all(t_stack *new, int free_content)
{
	t_stacknode	*node;

	while (new)
	{
		node = new->top->next;
		if (free_content)
			free (new->top->content);
		free(new);
		new->top = node;
	}
	free(new);
}

t_stack	*queue_map(t_stack *stack, void *(*func)(void *), int free_content)
{
	t_stacknode	*current;
	t_stacknode	*new_node;
	t_stack		*new_stack;

	if (!stack || !stack->bottom || !func)
		return (NULL);
	new_stack = stack_newstack();
	current = stack->bottom;
	while (current)
	{
		new_node = stack_newnode(func(current->content));
		if (!new_node)
		{
			ft_free_all(new_stack, free_content);
			return (NULL);
		}
		push(new_stack, current);
		current = current->previous;
	}
	return (new_stack);
}
