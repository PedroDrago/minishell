/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   evaluation.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rafaelro <rafaelro@student.42.rio>		 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/20 17:18:05 by pdrago			#+#	#+#			 */
/*   Updated: 2024/04/10 22:10:13 by rafaelro		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <sys/stat.h>

void	resolve_errors(char *command)
{
	struct stat	file_info;

	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(command, 2);
	if (stat(command, &file_info) < 0)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	if (!(file_info.st_mode & S_IXUSR))
	{
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	ft_putstr_fd(": Can't be executed by this shell\n", 2);
	exit(2);
}

int	execute_command(t_shell *shell, char **args)
{
	char	*path;

	execve(args[0], args, shell->envp);
	if (args[0] && args[0][0] == '.')
		resolve_errors(args[0]);
	path = get_right_path(shell, args[0]);
	execve(path, args, shell->envp);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	set_exit_status(1, shell);
	free_before_safely_exit(shell);
	exit(1);
}

int	perform_redirections(char **splited_command)
{
	int	i;
	int	original_fd;

	i = 0;
	original_fd = dup(0);
	while (splited_command[i])
	{
		if (is_redirect_input(splited_command[i]))
			redirect_input(splited_command[++i]);
		else if (is_redirect_output(splited_command[i]))
		{
			redirect_output(splited_command[i], splited_command[i + 1]);
			i++;
		}
		else if (is_heredoc(splited_command[i]))
			if (!do_heredoc(splited_command[++i], original_fd))
				return (FALSE);
		i++;
	}
	return (TRUE);
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

int	exec_list(t_list *list, t_shell *shell)
{
	t_node	*tmp;

	tmp = list->head;
	while (tmp)
	{
		execute_node(tmp, list, shell);
		tmp = tmp->next;
	}
	wait_children(shell);
	return (TRUE);
}

int	str_token_cmp(char *item) // NEWFEATURE
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

int	count_new_prompt_size(char *str) // NEWFEATURE
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

char	*prompt_pre_format(char *prompt, char *new_str, int i, int j) //NF
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

int	evaluate_prompt(char *prompt, t_shell *shell)
{
	t_list	*prompt_list;
	char	*tmp;

	prompt_list = NULL;
	tmp = malloc(sizeof(char) * (count_new_prompt_size(prompt) + 1));
	if (!tmp)
		return (FALSE);
	prompt_pre_format(prompt, tmp, 0, 0);
	free(prompt);
	prompt_list = parse_prompt(tmp);
	free(tmp);
	if (!prompt_list)
		return (FALSE);
	shell->prompt_list = prompt_list;
	setup_list_pipes(prompt_list);
	init_processes_data(prompt_list, shell);
	exec_list(prompt_list, shell);
	free_list(prompt_list);
	free_process_data(shell);
	return (TRUE);
}
