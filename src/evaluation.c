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
#include <fcntl.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


char **get_paths_split(t_shell *shell)
{
	char	**splited;
	t_env	*node;

	node = get_env_node(shell->env, "PATH");
	if (!node || !node->value)
		return (NULL);
	splited = ft_split(node->value, ':');
	if (!splited)
		return (NULL);
	return (splited);
}

char *get_current_path_str(char *path, char *command)
{
	char	*joined;

	joined = ft_strjoin(path, "/", O_ONE);
	if (!joined)
		return(NULL);
	joined = ft_strjoin(joined, command, O_ONE);
	if (!joined)
		return(NULL);
	return (joined);
}

int	can_open_file(int stat_return, struct stat *file_info)
{
	if (stat_return < 0)
		return (0);
	if (!(file_info->st_mode & S_IXUSR))
		exit(126);
	return (1);
}

char	*get_right_path(t_shell *shell, char *command) //FIX: Leak? Child process
{
	char	*path;
	char	**paths_split;
	int	i;
	struct stat	file_info; 

	i = 0;
	paths_split = get_paths_split(shell);
	if (!paths_split)
		return (NULL);
	while(paths_split[i])
	{
		path = get_current_path_str(paths_split[i++], command);
		if (can_open_file(stat(path, &file_info), &file_info))
			return (path);
	}
	exit(127);
}
int	execute_command(t_shell *shell, char *command, char **args)
{
	char *path;

	path = get_right_path(shell, command);
	execve(path, args, NULL);
	exit(1);
}

int	setup_list_pipes(t_list *list)
{
	t_node *tmp;
	int	pipe_fd[2];

	tmp = list->head;
	while(tmp)
	{
		if (tmp->has_pipe)
		{
			pipe(pipe_fd);
			tmp->node_pipe[1] = pipe_fd[1];
			tmp->next->node_pipe[0] = pipe_fd[0]; //WARN: Needs previous validation so that tmp->next won't be NULL;
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

int	is_token(char *str)
{
	if (!ft_strncmp(str, "<", 2))
		return (TRUE);
	if (!ft_strncmp(str, "<<", 3))
		return (TRUE);
	if (!ft_strncmp(str, ">>", 3))
		return (TRUE);
	if (!ft_strncmp(str, ">", 2))
		return (TRUE);
	if (!ft_strncmp(str, "|", 2))
		return (TRUE);
	return (FALSE);
}

int	is_pipe(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (TRUE);
	return (FALSE);
}

int	is_redirect_input(char *token)
{
	if (!ft_strncmp(token, "<", 2))
		return (TRUE);
	return (FALSE);
}

int	is_heredoc(char *token)
{
	if (!ft_strncmp(token, "<<", 3))
		return (TRUE);
	return (FALSE);
}

int	is_truncate(char *token)
{
	return (!ft_strncmp(token, ">", 2));
}

int	is_append(char *token)
{
	return (!ft_strncmp(token, ">>", 3));
}

int	is_redirect_output(char *token)
{
	return (is_truncate(token) || is_append(token));
}

int	do_heredoc(char *delimiter, int original_fd)
{
	int	pipe_fd[2];
	char *prompt;
	int	len;

	dup2(original_fd, 0);
	printf("DELIMITER: %s\n", delimiter);
	pipe(pipe_fd);
	prompt = readline("> ");
	if (!prompt)
		return (FALSE); // FIX: ????
	len = ft_strlen(delimiter);
	while (ft_strncmp(prompt, delimiter, len))
	{
		ft_putstr_fd(prompt, pipe_fd[1]); // FIX: ctrl+D e ctrl+C?
		ft_putstr_fd("\n", pipe_fd[1]);
		prompt = readline("> ");
		if (!prompt)
			return (FALSE); // FIX: ????
	}
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	return (TRUE);
}

int	perform_redirections(char **splited_command)
{
	int	i;
	int	tmp_fd;
	struct stat	file_info; 
	int		original_fd;

	i = 0;
	original_fd = dup(0);
	while(splited_command[i])
	{
		if(is_redirect_input(splited_command[i]))
		{
			i++;
			if (!can_open_file(stat(splited_command[i], &file_info), &file_info))
				exit (127);
			tmp_fd = open(splited_command[i], O_RDONLY);
			dup2(tmp_fd, 0);
		}
		else if(is_redirect_output(splited_command[i]))
		{
			if (is_append(splited_command[i]))
			{
				i++;
				if (!can_open_file(stat(splited_command[i], &file_info), &file_info))
					exit (127);
				tmp_fd= open(splited_command[i], O_RDWR | O_APPEND | O_CREAT, 0664);
			}
			else
			{
				i++;
				if (!can_open_file(stat(splited_command[i], &file_info), &file_info))
					exit (127);
				tmp_fd= open(splited_command[i], O_RDWR | O_TRUNC | O_CREAT, 0664);
			}
			dup2(tmp_fd, 1);
		}
		else if(is_heredoc(splited_command[i]))
		{
			i++;
			tmp_fd = do_heredoc(splited_command[i], original_fd);
		}
		i++;
	}
	return (TRUE);
}

char	**get_args(char **splited_command)
{
	char	**args;
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while(splited_command[i] && !is_pipe(splited_command[i]))
	{
		count++;
		i++;
		if (!splited_command[i] || is_pipe(splited_command[i]))
			break ;
		while (splited_command[i] && is_token(splited_command[i]))
			i += 2;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while(splited_command[i] && !is_pipe(splited_command[i]))
	{
		args[j++] = splited_command[i++];
		if (!splited_command[i] || is_pipe(splited_command[i]))
			break ;
		while (splited_command[i] && is_token(splited_command[i]))
			i += 2;
	}
	args[j] = NULL;
	return (args);
}

void	append_process(pid_t pid, t_shell *shell, char *basic_command)
{
	t_process	*process;
	char	**splited;

	process = malloc(sizeof(t_process));
	if (!process)
		exit(1);
	process->pid = pid;
	splited = command_split(basic_command);
	process->command = ft_strdup(splited[0]);
	free_split(splited);
	shell->processes_data.processes[shell->processes_data.index++] = process;
}

int	execute_node(t_node *node, t_list *list, t_shell *shell)
{
	char	**splited_command;
	char	**args;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		splited_command = command_split(node->basic_command);
		if (!splited_command)
			exit(1);
		args = get_args(splited_command);
		if (node->has_pipe)
		{
			dup2(node->node_pipe[1], 1);
		}
		if (node->prev && node->prev->has_pipe)
		{
			dup2(node->node_pipe[0], 0);
		}
		// WARN: EXPAND_ENVS()
		perform_redirections(splited_command);
		execute_command(shell, splited_command[0], args);
	}
	else
	{
		if (node->has_pipe)
			close(node->node_pipe[1]);
		if (node->prev && node->prev->has_pipe)
			close(node->node_pipe[0]);
		append_process(pid, shell, node->basic_command);
	}
	(void) list;
	return (TRUE);
}
void	resolve_error(int status, char *command)
{
	if (status == 32512)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
	else if (status == 32256)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}

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

int	validate_splited_command(char **splited_command)
{
	int	i;

	i = 0;
	while(splited_command[i])
	{
		if (is_pipe(splited_command[i]))
			break ;
		if (is_token(splited_command[i]))
		{
			if (!splited_command[i + 1])
				return (ft_putstr_fd("Minishell: Syntax error [Unresolved Token]\n", 2), FALSE);
			else if (is_token(splited_command[i + 1]))
				return (ft_putstr_fd("Minishell: Syntax error [Double Token]\n", 2), FALSE);
		}
		i++;
	}
	return (TRUE);
}
int	validate_list(t_list *list)
{
	t_node *tmp;
	char	**splited_command;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->has_pipe && !tmp->next)
			return (ft_putstr_fd("Minishell: Syntax error [void pipe]\n", 2), FALSE);
		splited_command = command_split(tmp->basic_command);
		if (!validate_splited_command(splited_command))
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

void	init_processes_data(t_list *list, t_shell *shell)
{
	int	i;
	t_node *tmp;

	tmp = list->head;
	i = 0;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	shell->processes_data.processes = malloc(sizeof(t_process *) * i);
	shell->processes_data.size = i;
	shell->processes_data.index = 0;
}

int	evaluate_prompt(char *prompt, t_shell *shell)
{
	t_list	*prompt_list;

	prompt_list = parse_prompt(prompt);
	if (!prompt_list)
		return (FALSE);
	shell->prompt_list = prompt_list;
	if (!validate_list(prompt_list))
		return (TRUE);
	setup_list_pipes(prompt_list);
	init_processes_data(prompt_list, shell);
	exec_list(prompt_list, shell);
	return (TRUE);
}

/*
* TODO:
* - [ ] update free_split to new list.
* - [ ] make basic_command split before forking, maybe on the node creatin already.
* - [ ] Execute builtins before fork() (basically the same logic but without forking)
* - [ ] Remove deprecated fields in node, and update whole project
* */
