/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:48:43 by rafaelro          #+#    #+#             */
/*   Updated: 2024/03/21 01:02:44 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
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

void		expand_arguments(t_list *list, t_shell *shell);
char		*split_join(char **splited);
int			is_valid_arg_char(char c);
char		**ft_split_charset_mod(char *str, char *charset);
char		*dup_value(char *arg);
int	env(t_env *env);
t_env		*get_env_node(t_env *env, char *key);
int			set_env_value(t_env *env, char *key, char *value);
t_env		*load_envs(char *envp[]);
char		**split_keyvalue(char *str, char sep);
void		free_env(t_env *env);
t_env		*fill_env_struct(int fd);
int	cd(char *argv[], t_shell *shell);
int	pwd(void);
int	export(char *argv[], t_shell *shell);
int	unset(char *argv[], t_shell *shell);
void		exit_safely(t_shell *shell);
void		set_exit_status(int status, t_shell *shell);
void		free_split(char **splited);
void		print_split(char **argv);
void		free_list(t_list *list);
void		print_list(t_list *arg);
int			split_len(char **split);
char		*get_cwd(void);
t_env		*make_new_env_node(char *key, char *value);
int			is_pipe(char *token);
void	pipe_output(t_node *node, t_shell *shell);
int			is_redirect_output(char *token);
int	is_redirect_input(char *token);
int			open_file(t_node *current);
int	execute_command(t_shell *shell, char *command, char **args);
int			is_builtin(char *command);
void	execute_builtin(t_node *node, t_shell *shell);
t_list *parse_prompt(char *prompt);
int			fill_list(char **splited, t_list *list);
t_shell		*init_shell(int argc, char *argv[], char *envp[]);
char		*get_prompt(t_shell *shell);
int			valid_quotes(char *prompt);
int			evaluate_prompt(char *prompt, t_shell *shell);
t_node		*create_node(void);
void		append_node(t_list *list, t_node *node);
t_list		*create_list(void);
char	**command_split(char *str);
int			has_invalid_characters(char **splited);
void		resolve_quotes(char c, int *in_single_quote, int *in_double_quote);
int			is_splitable(char *str, int end, int in_single_quotes,
				int in_double_quotes);
int			count_split(char *str);
void	redirect_output(char *file);
void		exit_program(int sig);
int			count_backslash(char *str, int start, int end);
void	resolve_error(int status, char *command);
void	wait_for_child(int *old_yield, int pid, t_shell *shell, t_node *current);
int	is_heredoc(char *token);
void	redirect_input(char *file);
int	heredoc(t_node *current, t_shell *shell, int fd_out);
char	**get_args(char **splited_command);
int	perform_redirections(char **splited_command);
int	echo(char *argv[]);
int	perform_builtin_redirections(char **splited_command);

char	**prompt_split(char *str);
#endif
