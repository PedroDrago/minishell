/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:48:43 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/26 14:38:31 by rafaelro         ###   ########.fr       */
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

//arg_expansion.c
void	resolve_quotes(char c, int *in_single_quote, int *in_double_quote);
char	*get_expanded_arg(char *arg, t_shell *shell);
char	**expand_split(char **splited, t_shell *shell);
void	expand_arguments(t_node *node, t_shell *shell);
//builtins.c
void		perform_builtin_redirections(char **splited_com, int *status, int original_fd);
int		is_builtin(char *command);
int		prep_builtin(t_node *node);
void	post_builtin(t_node *node, t_shell *shell);
void	execute_builtin(t_node *node, t_shell *shell);
void	builtin_exit(t_shell *shell, t_node *node);
//cd.c
int		cd(char *argv[], t_shell *shell);
char	*get_home_path(t_env *env);
//command_split.c
char	*command_split_substr(char *str, int start, int end);
void	do_command_split(char *str, char **splited);
char	**command_split(char *str);
//command_split_utils.c
int		is_splitable(char *str, int end, int in_single_quotes,
			int in_double_quotes);
int		count_command_split(char *str);
int		count_backslash(char *str, int start, int end);
//echo.c
int		split_len(char **split);
int		echo(char *argv[]);
//env.c
int		env(t_env *env);
t_env	*get_env_node(t_env *env, char *key);
int		insert_new_node(t_env *env, char *key, char *value);
int		set_env_value(t_env *env, char *key, char *value);
t_env	*load_envs(char *envp[]);
//env_split.c
int		do_edge_cases(char **splited, char *str, char sep);
char	**split_keyvalue(char *str, char sep);
//env_utils.c
void	free_env(t_env *env);
t_env	*make_new_env_node(char *key, char *value);
int		fill_node(char *str, int fd, t_env *temp_env, t_env *env_head);
t_env	*fill_env_struct(int fd);
//evaluation.c
int		execute_command(t_shell *shell, char **args);
int		perform_redirections(char **splited_command);
void	wait_children(t_shell *shell);
int		evaluate_prompt(char *prompt, t_shell *shell);
int		exec_list(t_list *list, t_shell *shell);
//execution_path.c
char	**get_paths_split(t_shell *shell);
char	*get_current_path_str(char *path, char *command);
int	can_open_file(int stat_return, struct stat *file_info, char *command, t_shell *shell);
char	*get_right_path(t_shell *shell, char *command);
//expansion_edge_cases.c
char	*dup_value(char *arg);
//export.c
void	print_export(t_env *env, int fd_out);
int		is_valid(char *key);
int		export(char *argv[], t_shell *shell);
//heredoc.c
int		is_heredoc(char *token);
int		do_heredoc(char *delimiter, int original_fd);
int		do_heredoc_builtin(char *delimiter, int original_fd);
//input_redirection.c
int		is_redirect_input(char *token);
int		redirect_input_builtin(char *file);
void	redirect_input(char *file);
//list_validations.c
int		validate_splited_command(char **splited_command);
int		validate_list(t_shell *shell, t_list *list);
int		validate_prompt(char *prompt, t_shell *shell);
//exits.c
void	exit_program(int sig);
void	exit_safely(t_shell *shell, unsigned char status);
void	free_before_safely_exit(t_shell *shell);
//node_args.c
char	**get_args(char **splited_command);
//output_redirections.c
int		is_truncate(char *token);
int		is_append(char *token);
int		is_redirect_output(char *token);
void	redirect_output(char *redirection, char *file);
int		redirect_output_builtin(char *redirection, char *file);
//parser.c
t_node	*create_node(void);
void	append_node(t_list *list, t_node *node);
t_list	*create_list(void);
t_list	*parse_prompt(char *prompt);
t_list	*parse_prompt(char *prompt);
//pipe.c
int		setup_list_pipes(t_list *list);
int		is_token(char *str);
int		is_pipe(char *token);
//process.c
void	append_process(pid_t pid, t_shell *shell);
int		prep_process(t_node *node);
void	post_process(pid_t pid, t_node *node, t_shell *shell);
int		execute_node(t_node *node, t_list *list, t_shell *shell);
void	init_processes_data(t_list *list, t_shell *shell);
void	free_process_data(t_shell *shell);
void	strip_quotes(t_node *node);
//prompt_setup.c
char	*get_env_node_value(t_env *env, char *key);
char	*get_prompt_user(char *str, t_shell *shell);
char	*get_prompt_pwd(char *str, t_shell *shell);
char	*get_prompt_string(t_shell *shell);
char	*get_prompt(t_shell *shell);
//prompt_split.c
char	*prompt_split_substr(char *str, int start, int end);
void	do_prompt_split(char *str, char **splited, int start, int end);
char	**prompt_split(char *str);
//pwd.c
int		pwd(void);
//shell_setting.c
char	*get_cwd(void);
t_shell	*init_shell(int argc, char *argv[], char *envp[]);
//split_charset.c
int		is_charset(char c, char *charset);
int		charset_split_count(char *str, char *charset);
char	*ft_strndup(char *str, int n);
char	**split_loop(char **splited, char *str, char *charset);
char	**ft_split_charset_mod(char *str, char *charset);
//split_join.c
void	init_vars(int *j, int *z, int *single_q, int *double_q);
int		split_str_len(char **splited);
int		is_valid_arg_char(char c);
void	split_join_loop(char **splited, char *join, int z);
char	*split_join(char **splited);
//unset.c
void	free_node(t_env *env);
int		remove_node(t_env **env, char *key);
int		unset(char *argv[], t_shell *shell);
//utils.c
void	set_exit_status(int status, t_shell *shell);
void	free_split(char **splited);
void	print_split(char **argv);
void	free_list(t_list *list);
void	print_list(t_list *arg);
//validations.c
int		has_double_token(char *prompt);
int		valid_quotes(char *prompt);
int		has_invalid_characters(char **splited);
//quote_split.c
char	**quote_split(char *str);
//double_token_validation.c
int		validate_double_tokens(char *prompt);
void	init_flags(t_validation *flags, int *count);
int		is_token_char(char c);
//character_validation.c
int		validate_characters(char *prompt);
extern int	g_sig;

#endif
