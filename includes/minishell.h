/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:48:43 by rafaelro          #+#    #+#             */
/*   Updated: 2024/05/09 19:19:38 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>

// arg_expansion.c
void			expand_arguments(t_node *node, t_shell *shell);
char			**expand_split(char **splited, t_shell *shell);
char			*get_expanded_arg(char *arg, t_shell *shell);
void			resolve_quotes(char c, int *in_single_quote,
					int *in_double_quote);
// builtins.c
void			builtin_exit(t_shell *shell, t_node *node);
int				execute_builtin(t_node *node, t_shell *shell, int *prevpipe,
					int *pipefd);
int				is_builtin(char *command);
void			perform_builtin_redirections(char **splited_com, int *status,
					int original_fd, t_shell *shell);
int				prep_builtin(t_node *node, t_shell *shell, int *prevpipe,
					int *pipefd);
void			post_builtin(t_node *node, int *prevpipe, int *pipefd);
// cd.c
int				cd(char *argv[], t_shell *shell);
char			*get_home_path(t_env *env);
// command_split.c
char			**command_split(char *str);
char			*command_split_substr(char *str, int start, int end);
void			do_command_split(char *str, char **splited);
// command_split_utils.c
int				count_command_split(char *str);
int				is_splitable(char *str, int end, int in_single_quotes,
					int in_double_quotes);
// echo.c
int				echo(char *argv[]);
int				split_len(char **split);
// env.c
int				env(t_env *env);
t_env			*get_env_node(t_env *env, char *key);
int				insert_new_node(t_env *env, char *key, char *value);
t_env			*load_envs(char *envp[]);
int				set_env_value(t_env *env, char *key, char *value);
int				set_env_value2(t_env *env, char *key, char *value);
// env_split.c
int				do_edge_cases(char **splited, char *str, char sep);
char			**split_keyvalue(char *str, char sep);
// env_utils.c
void			free_env(t_env *env);
int				fill_node(char *str, int fd, t_env *temp_env, t_env *env_head);
t_env			*make_new_env_node(char *key, char *value);
// evaluation.c
int				evaluate_prompt(char *prompt, t_shell *shell);
int				exec_list(t_list *list, t_shell *shell);
int				execute_command(t_shell *shell, char **args);

int				perform_redirections(int i, char **splited_command,
					t_shell *shell, int *prevpipe);
// unquoting.c
void			str_unquote(char **str);
// evaluation_utils.c
void			check_for_pipes(t_shell *shell);
int				count_new_prompt_size(char *str);
char			*prompt_pre_format(char *prompt, char *new_str, int i, int j);
int				str_token_cmp(char *item);
void			wait_children(t_shell *shell);
// execution_path.c
int				can_open_file(int stat_return, struct stat *file_info,
					char *command, t_shell *shell);
char			*get_current_path_str(char *path, char *command);
char			**get_paths_split(t_shell *shell);
char			*get_right_path(t_shell *shell, char *command);
// exits.c
void			exit_program(int sig);
void			exit_safely(t_shell *shell, unsigned char status);
void			free_before_safely_exit(t_shell *shell);
void			set_builtin_exit_status(t_shell *shell, int status);
// exits2.c
void			exit_redirect_output(t_shell *shell, char *file, int status);
// exit_utils.c
void			exit_ultra_safe(t_shell *shell);
void			free_and_exit_builtin(t_shell *shell, t_node *node);
long long int	ft_atolli_mod(const char *nptr);
int				is_numeric_argument(char *str);
int				is_valid_lli(char *status);
// expansion_edge_cases.c
char			*dup_value(char *arg);
// export.c
int				export(char *argv[], t_shell *shell);
int				is_valid(char *key);
void			print_export(t_env *env, int fd_out);
// heredoc.c
int				do_heredoc(char *delimiter, int prevpipe, t_shell *shell);
void			do_heredoc_builtin(char *delimiter, int original_fd,
					t_shell *shell);
int				is_heredoc(char *token);
// heredoc2.c
void			post_heredoc(int *pipe_fd, int *prevpipe);
// input_redirection.c
int				is_redirect_input(char *token);
void			redirect_input(char *file, t_shell *shell, int prevpipe);
int				redirect_input_builtin(char *file);
// node_args.c
char			**get_args(char **splited_command);
// output_redirections.c
int				is_append(char *token);
int				is_redirect_output(char *token);
int				is_truncate(char *token);
void			redirect_output(char *redirection, char *file, t_shell *shell);
int				redirect_output_builtin(char *redirection, char *file);
// parser.c
void			append_node(t_list *list, t_node *node);
t_list			*create_list(void);
t_node			*create_node(void);
t_list			*parse_prompt(char *prompt);
// pipe.c
int				is_token(char *str);
int				is_pipe(char *token);
int				setup_list_pipes(t_list *list);
// process.c
void			append_process(pid_t pid, t_shell *shell);
int				execute_node(t_node *node, t_shell *shell, int *prevpipe);
void			init_processes_data(t_list *list, t_shell *shell);
int				prep_process(t_node *node, t_shell *shell, int *prevpipe,
					int *pipefd);
void			post_process(pid_t pid, t_shell *shell, int *prevpipe,
					int *pipefd);
// process_utils.c
void			free_process_data(t_shell *shell);
// prompt_setup.c
char			*get_env_node_value(t_env *env, char *key);
char			*get_prompt(t_shell *shell);
char			*get_prompt_pwd(char *str, t_shell *shell);
char			*get_prompt_string(t_shell *shell);
char			*get_prompt_user(char *str, t_shell *shell);
// prompt_split.c
void			do_prompt_split(char *str, char **splited, int start, int end);
char			*prompt_split_substr(char *str, int start, int end);
char			**prompt_split(char *str);
// pwd.c
int				pwd(void);
// quote_split.c
char			**quote_split(char *str);
// shell_setting.c
char			*get_cwd(void);
t_shell			*init_shell(t_shell *shell, int argc, char *argv[],
					char *envp[]);
// split_charset.c
int				charset_split_count(char *str, char *charset);
char			**ft_split_charset_mod(char *str, char *charset);
char			*ft_strndup(char *str, int n);
int				is_charset(char c, char *charset);
char			**split_loop(char **splited, char *str, char *charset);
// split_join.c
void			init_vars(int *j, int *z, int *single_q, int *double_q);
int				is_valid_arg_char(char c);
char			*split_join(char **splited);
void			split_join_loop(char **splited, char *join, int z);
int				split_str_len(char **splited);
// unquoting
void			uncontrol_args(char **args);
char			*uncontrol_arg(char *arg);
// unset.c
void			free_node(t_env *env);
int				remove_node(t_env **env, char *key);
int				unset(char *argv[], t_shell *shell);
// utils.c
void			free_list(t_list *list);
void			free_split(char **splited);
void			print_split(char **argv);
void			print_list(t_list *arg);
void			set_exit_status(int status, t_shell *shell);
// validations.c
int				validate_prompt(char *prompt, t_shell *shell);
// double_token_validation.c
void			init_flags(t_validation *flags, int *count);
int				is_token_char(char c);
int				validate_double_tokens(char *prompt);
// global_var
extern int		g_sig;

void			get_current_envp(t_shell *shell);
#endif
