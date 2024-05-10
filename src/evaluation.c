/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:37:31 by pdrago            #+#    #+#             */
/*   Updated: 2024/05/08 16:29:40 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	while (args[0] && ft_strlen(args[0]) <= 0)
		args++;
	if (!args[0])
	{
		free_before_safely_exit(shell);
		exit(0);
	}
	uncontrol_args(args);
	if (ft_atoi(get_env_node_value(shell->env, "?")) == 0)
	{
		execve(args[0], args, shell->env_array);
		if (args[0] && (args[0][0] == '.' || args[0][0] == '/'))
			resolve_errors(args[0], shell);
		path = get_right_path(shell, args[0]);
		if (path)
			execve(path, args, shell->env_array);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	set_exit_status(1, shell);
	free_before_safely_exit(shell);
	exit(1);
}

int	perform_redirections(int i, char **splited, t_shell *shell, int *prevpipe)
{
	int	pipe_fd[2];

	while (splited[i])
	{
		if (ft_atoi(get_env_node_value(shell->env, "?")) != 0)
			return (FALSE);
		if (is_redirect_input(splited[i]))
			redirect_input(splited[++i], shell, *prevpipe);
		else if (is_redirect_output(splited[i]))
		{
			redirect_output(splited[i], splited[i + 1], shell);
			i++;
		}
		else if (is_heredoc(splited[i]))
		{
			pipe(pipe_fd);
			while (splited[i] && is_heredoc(splited[i]))
				if (!do_heredoc(splited[++i], pipe_fd[1], shell) || !(++i))
					return (FALSE);
			post_heredoc(pipe_fd, prevpipe);
			continue ;
		}
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
	close(bkp_stdout);
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
	init_processes_data(prompt_list, shell);
	check_for_pipes(shell);
	exec_list(prompt_list, shell);
	free_list(prompt_list);
	shell->prompt_list = NULL;
	free_process_data(shell);
	return (TRUE);
}
