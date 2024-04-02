/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:25 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:38:25 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

t_list *parse_prompt(char *prompt)
{
	t_list	*prompt_list;
	char	**command_tab;
	t_node	*node;
	int	i;


	prompt_list = create_list();
	if (!prompt_list)
		return (NULL);
	i = 0;
	command_tab = prompt_split(prompt);
	while(command_tab[i])
	{
		node = create_node();
		node->basic_command = command_tab[i];
		if (command_tab[i][ft_strlen(command_tab[i]) - 1] == '|')
			node->has_pipe = TRUE;
		node->splited_command = command_split(command_tab[i]);
		i++;
		append_node(prompt_list, node);
	}
	return (prompt_list);
}
