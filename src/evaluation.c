/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:05 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/21 19:09:14 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	execute_command(t_shell *shell, char *command, char **args)
{
	char *path;

	execve(command, args, shell->envp);
	path = get_right_path(shell, command);
	execve(path, args, shell->envp);
	exit(1);
}

int	perform_redirections(char **splited_command)
{
	int	i;
	int		original_fd;

	i = 0;
	original_fd = dup(0);
	while(splited_command[i])
	{
		if(is_redirect_input(splited_command[i]))
			redirect_input(splited_command[++i]);
		else if(is_redirect_output(splited_command[i]))
			redirect_output(splited_command[++i]);
		else if(is_heredoc(splited_command[i]))
	        {
			if (!do_heredoc(splited_command[++i], original_fd))
			    return (FALSE);
			
		}
		i++;
	}
	return (TRUE);
}

void	wait_children(t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < shell->processes_data.size)
	{
		status = -1;
		waitpid(shell->processes_data.processes[i]->pid, &status, 0);
		set_exit_status(status, shell);
		if (status > 0)
			resolve_error(status, shell->processes_data.processes[i]->command);
		i++;
	}
}

int	exec_list(t_list *list, t_shell *shell)
{
	t_node *tmp;

	tmp = list->head;
	while (tmp)
	{
		execute_node(tmp, list, shell);
		tmp = tmp->next;
	}
	wait_children(shell);
	return (TRUE);
}

int    str_token_cmp(char *item) // NEWFEATURE
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

int        count_new_prompt_size(char *str) // NEWFEATURE
{
    int    count;

    count = 0;
    while (str && *str)
    {
        if (ft_strchr("\"><|", *str++))
            count++;
        count++;
    }
    return (count);
}

char    *prompt_pre_format(char *prompt, char *new_str) // NEWFEATURE
{
    int i;
    int j;
    int    diff;
    int    quotes;

    i = 0;
    j = 0;
    quotes = 0;
    while (prompt[j])
    {
        if (prompt[j] == '\"')
            quotes = !quotes;
        diff = str_token_cmp(&prompt[j]);
        if (!quotes && diff)
        {
            new_str[i++] = ' ';
            while(diff-- > 0)
                new_str[i++] = prompt[j++];
            new_str[i++] = ' ';
            continue;
        }
        new_str[i++] = prompt[j++];
    }
    new_str[i] = '\0';
    return new_str;
}

int	evaluate_prompt(char *prompt, t_shell *shell)
{
	t_list	*prompt_list;
	char	*tmp;

	tmp = malloc(sizeof(char) * (count_new_prompt_size(prompt) + 1));
	if (!tmp)
		return (FALSE);
	prompt_pre_format(prompt, tmp);
	prompt_list = parse_prompt(tmp);
	if (!prompt_list)
		return (FALSE);
	shell->prompt_list = prompt_list;
	if (!validate_list(prompt_list))
		return (TRUE); //WARN: free alguma coisa
	setup_list_pipes(prompt_list);
	init_processes_data(prompt_list, shell);
	exec_list(prompt_list, shell);
	free_list(prompt_list);
	free_process_data(shell);
	return (TRUE);
}
