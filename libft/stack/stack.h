/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 09:33:03 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:50:41 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

typedef struct s_stacknode
{
	void				*content;
	struct s_stacknode	*next;
	struct s_stacknode	*previous;
}	t_stacknode;
typedef struct s_stack
{
	t_stacknode	*top;
	t_stacknode	*bottom;
	size_t		size;
}	t_stack;

t_stacknode	*stack_newnode(void *content);
t_stacknode	*pop(t_stack *stack);
t_stack		*stack_newstack(void);
t_stack		*stack_map(t_stack *stack, void (*func)(void *));
void		push(t_stack *stack, t_stacknode *node);
void		stack_clear(t_stack *stack, int free_content);
void		stack_iter(t_stack *stack, void (*func)(void *));
