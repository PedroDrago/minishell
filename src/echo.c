#include "../includes/minishell.h"
#include <stdio.h>

int	echo(int argc, char *argv[], int fd_out)
{
	int	flag;
	int	count;

	flag = 0;
	count = 0;
	if (argc > 0 && argv && argv[0] && argv[1] && argv[1][0] == '-')
	{
		if (!ft_strncmp(argv[1], "-n", 3))
		{
			flag = 1;
			count++;
		}
	}
	count++;
	while (argv && argv[count])
	{
		ft_putstr_fd(argv[count], fd_out);
		if (count != (argc - 1))
			ft_putstr_fd(" ", fd_out);
		count++;
	}
	if (!flag)
		ft_putstr_fd("\n", fd_out);
	return (0);
}

int	split_len(char **split)
{
	int	len;

	len = 0;
	while(split[len])
		len++;
	return (len);
}

int	exec_echo(t_node *command, int fd_out)
{
	if (!command->token)
		echo(split_len(command->args), command->args, 1);
	else
		echo(split_len(command->args), command->args, fd_out);
	return (TRUE);
}
