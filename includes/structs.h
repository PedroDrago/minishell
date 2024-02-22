#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_shell
{
	int	last_status;
	char	*shell_path;
	char	*path;

}	t_shell;

typedef struct s_node
{
	char *command;
	char **args;
	char *token;
	struct s_node *next;
}	t_node;

typedef struct s_list
{
	t_node *head;
	t_node *tail;
}	t_list;
#endif
