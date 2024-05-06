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

void	resolve_errors(char *command, t_shell *shell)
{
	struct stat	file_info;

	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(command, 2);
	if (stat(command, &file_info) < 0)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		free_before_safely_exit(shell);
		exit(127);
	}
	if (!(file_info.st_mode & S_IXUSR))
	{
		ft_putstr_fd(": Permission denied\n", 2);
		free_before_safely_exit(shell);
		exit(126);
	}
	if (S_ISDIR(file_info.st_mode))
	{
		ft_putstr_fd(": Is a directory\n", 2);
		free_before_safely_exit(shell);
		exit(126);
	}
	ft_putstr_fd(": Can't be executed by this shell\n", 2);
	free_before_safely_exit(shell);
	exit(0);
}

int	execute_command(t_shell *shell, char **args)
{
	char	*path;

	if (!args[0])
	{
		free_before_safely_exit(shell);
		exit(0);
	}
	//printf("%d \n", ft_atoi(get_env_node_value(shell->env, "?")));
	if (ft_atoi(get_env_node_value(shell->env, "?")) == 0)
	{
		execve(args[0], args, shell->envp);
		if (args[0] && (args[0][0] == '.' || args[0][0] == '/'))
			resolve_errors(args[0], shell);
		path = get_right_path(shell, args[0]);
		execve(path, args, shell->envp);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	set_exit_status(1, shell);
	free_before_safely_exit(shell);
	exit(1);
	
}

int	perform_redirections(char **splited_command, t_shell *shell, int *prevpipe)
{
	int	i;

	i = 0;
	while (splited_command[i])
	{
		if (ft_atoi(get_env_node_value(shell->env, "?")) != 0)
			return (FALSE);
		if (is_redirect_input(splited_command[i]))
			redirect_input(splited_command[++i], shell, *prevpipe);
		else if (is_redirect_output(splited_command[i]))
		{
			redirect_output(splited_command[i], splited_command[i + 1], shell);
			i++;
		}
		else if (is_heredoc(splited_command[i]))
			if (!do_heredoc(splited_command[++i], *prevpipe, shell))
				return (FALSE);
		i++;
	}
	return (TRUE);
}

int	exec_list(t_list *list, t_shell *shell)
{
	t_node	*tmp;
	int		prevpipe;
	int		bkp_stdout;

	prevpipe = dup(STDIN_FILENO);
	bkp_stdout = dup(STDOUT_FILENO);
	tmp = list->head;
	while (tmp)
	{
		execute_node(tmp, shell, &prevpipe);
		tmp = tmp->next;
		dup2(bkp_stdout, STDOUT_FILENO);
	}
	wait_children(shell);
	return (TRUE);
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
	/*setup_list_pipes(prompt_list);*/
	init_processes_data(prompt_list, shell);
	check_for_pipes(shell);
	exec_list(prompt_list, shell);
	free_list(prompt_list);
	shell->prompt_list = NULL;
	free_process_data(shell);
	return (TRUE);
}
