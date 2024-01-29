/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 09:41:15 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:48:48 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

typedef struct s_listnode
{
	void				*content;
	struct s_listnode	*next;
	struct s_listnode	*previous;
}	t_listnode;
typedef struct s_list
{
	t_listnode	*head;
	t_listnode	*tail;
	size_t		size;
}	t_list;

t_listnode	*list_newnode(void *content);
t_listnode	*list_removenode(t_list *list, t_listnode *node);
void		list_addfront(t_list *lst, t_listnode *new);
void		list_addback(t_list *lst, t_listnode *new);
void		list_delnode(t_listnode *node, int free_content);
void		list_clear(t_list *lst, int free_content);
void		list_iter(t_list *lst, void (*f)(void *));
t_list		*list_newlist(void);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), int free_content);
