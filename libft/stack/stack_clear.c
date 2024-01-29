/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:06:42 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:49:09 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	stack_clear(t_stack *stack, int free_content)
{
	t_stacknode	*tmp;

	if (!stack || stack->top)
		return ;
	while (stack->top)
	{
		tmp = stack->top->next;
		if (free_content)
			free (stack->top->content);
		free (stack->top);
		stack->top = tmp;
	}
	stack->size = 0;
}
