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

int	valid_prompt(char *prompt);
int	resolve_prompt(char *prompt, t_shell *shell);
int	fill_flags(char **splited, t_command *command);
void	free_split(char **splited);
int	fill_command(t_command *command, char **splited);
int	resolve_command(t_command command, t_shell *shell);
char	*read_file(int fd);
long	copy_final_line(char *str, char *tmp, int start);
long	get_history_count(int fd);
int	register_command(char *prompt, int fd);
int	valid_prompt(char *prompt);
int	resolve_prompt(char *prompt, t_shell *shell);
char *parse_path(char *str);
int	set_paths(t_shell *shell, char *execution_path);
int	init_shell(t_shell *shell, int argc, char *execution_path);
int	valid_characters(char *prompt);

#endif
