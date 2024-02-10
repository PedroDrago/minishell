#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_command
{
	char *command;
	char **args;
}	t_command;

typedef struct s_shell
{
	int	history_fd;
	int	last_status;
	char	*shell_path;
	char	*path;

}	t_shell;
#endif
