/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_iter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:08:43 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:09:11 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	queue_iter(t_stack *stack, void (*func)(void *))
{
	t_stacknode	*current;

	current = stack->top;
	while (current)
	{
		func(current->content);
		current = current->next;
	}
}
