/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:48:43 by rafaelro          #+#    #+#             */
/*   Updated: 2024/03/13 21:05:13 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "macros.h"
# include "structs.h"
# include "../libft/libft.h"

# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

extern int	g_pid;
//history
char	*read_file(int fd);
long	copy_final_line(char *str, char *tmp, int start);
long	get_history_count(int fd);
int	register_command(char *prompt, int fd);

//parser
t_node *create_node();
void append_node(t_list *list,t_node *node);
t_list *create_list();
int    is_token(char *item);
t_list	*generate_list(char *prompt, t_shell *shell);
void free_list(t_list *list);


//evaluate
int    evaluate_prompt(char *prompt, t_shell *shell);
int *pipe_command(t_node *current, int *fds);

//shell settings
char	*parse_path(char *str);
char	*get_cwd(void);
int	set_paths(t_shell *shell, char *execution_path);
t_shell *init_shell(char *envp[]);
void	terminate_shell(t_shell *shell);


//utils
void print_list(t_list *arg);
void print_split(char **argv);
void	free_split(char **splited);


//validations
int	valid_prompt(char *prompt);
int	valid_characters(char *prompt);

//nev
t_env	*load_envs(char *envp[]);
int		set_env_value(t_env *env, char *key, char *value);
t_env	*get_env_node(t_env *env, char *key);
int	env(t_env *env, int fd_out);
void	free_env(t_env *env);

//signal
void	exit_program(int n);

char **prompt_split(char *s);
void expand_arguments(t_list *list, t_shell *shell);


int	is_redirect_input(char *token);
int	is_heredoc(char *token);
int	is_redirect_output(char *token);
void	execute_redirection(t_node *current, t_shell *shell, int *old_yield, int file);
void	redirect_output(t_node *current, t_shell *shell, int *old_yield);
int	execute_command(t_shell *shell, t_node *current);
void	execute_pipe(t_node *current, t_shell *shell, int *old_yield, int *new_yield);
int	*pipe_output(t_node *current, int *old_yield, t_shell *shell);
int	is_pipe(char *token);


int	pwd(int fd_out);
int	echo(int argc, char *argv[], int fd_out);
int	split_len(char **split);
void	exit_safely(t_shell *shell);
int	is_builtin(char *command);
void	exec_builtin(t_node *current, t_shell *shell, int fd_out);
int	unset(t_node *current, t_shell *shell);
char	**split_keyvalue(char *str, char sep);
int	export(t_node *node, t_shell *shell, int fd_out);
int	cd(t_node *node, t_shell *shell);
#endif
