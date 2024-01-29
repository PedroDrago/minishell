/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:04:30 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:49:33 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stacknode	*pop(t_stack *stack)
{
	t_stacknode	*node;

	if (!stack || !stack->top)
		return (NULL);
	node = stack->top;
	stack->size--;
	if (!node->next)
	{
		stack->top = NULL;
		stack->bottom = NULL;
	}
	else
	{
		node->next->previous = NULL;
		stack->top = node->next;
	}
	node->next = NULL;
	node->previous = NULL;
	return (node);
}
