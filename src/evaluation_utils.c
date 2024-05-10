/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:18:31 by rafaelro          #+#    #+#             */
/*   Updated: 2024/05/07 16:17:39 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	str_token_cmp(char *item)
{
	if (!item)
		return (1);
	else if (!ft_strncmp(item, "|", 1))
		return (1);
	else if (!ft_strncmp(item, "<<", 2))
		return (2);
	else if (!ft_strncmp(item, "<", 1))
		return (1);
	else if (!ft_strncmp(item, ">>", 2))
		return (2);
	else if (!ft_strncmp(item, ">", 1))
		return (1);
	return (0);
}

int	count_new_prompt_size(char *str)
{
	int	count;

	count = 0;
	while (str && *str)
	{
		if (ft_strchr("\"><|", *str++))
			count += 2;
		count++;
	}
	return (count);
}

char	*prompt_pre_format(char *prompt, char *new_str, int i, int j)
{
	int	diff;
	int	quotes;
	int	d_quotes;

	quotes = 0;
	d_quotes = 0;
	while (prompt[j])
	{
		if (prompt[j] == '\"' && !quotes)
			d_quotes = !d_quotes;
		if (prompt[j] == '\'' && !d_quotes)
			quotes = !quotes;
		diff = str_token_cmp(&prompt[j]);
		if (!d_quotes && !quotes && diff)
		{
			new_str[i++] = ' ';
			while (diff-- > 0)
				new_str[i++] = prompt[j++];
			new_str[i++] = ' ';
			continue ;
		}
		new_str[i++] = prompt[j++];
	}
	new_str[i] = '\0';
	return (new_str);
}

void	wait_children(t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < shell->pids.size)
	{
		status = -1;
		waitpid(shell->pids.array[i], &status, 0);
		set_exit_status(WEXITSTATUS(status), shell);
		i++;
	}
}

void	check_for_pipes(t_shell *shell)
{
	t_node	*temp;

	temp = shell->prompt_list->head;
	while (temp)
	{
		if (temp->has_pipe)
		{
			shell->has_pipes = 1;
			return ;
		}
		temp = temp->next;
	}
}
