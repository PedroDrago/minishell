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
t_list *generate_list(char *prompt);


//evaluate
int    evaluate_prompt(char *prompt, t_shell *shell);
int *pipe_command(t_node *current, int *fds);

//shell settings
char	*parse_path(char *str);
char	*get_cwd(void);
int	set_paths(t_shell *shell, char *execution_path);
int	init_shell(t_shell *shell, int argc, char *execution_path);


//utils
void print_list(t_list *arg);
void print_split(char **argv);
void	free_split(char **splited);


//validations
int	valid_prompt(char *prompt);
int	valid_characters(char *prompt);
#endif
