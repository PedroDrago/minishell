#include "../includes/minishell.h"

void	set_exit_status(int status, t_shell *shell)
{
	char	*status_string;

	status_string = ft_itoa(status);
	if (!status_string)
		exit_safely(shell, 1);
	if (!set_env_value(shell->env, "?", status_string))
		exit_safely(shell, 1);
	free(status_string);
}

void	free_split(char **splited)
{
	int	count;

	count = -1;
	if (!splited)
		return ;
	while (splited[++count])
		free(splited[count]);
	free(splited);
}

void	print_split(char **argv)
{
	int	i;

	i = 0;
	printf("**********SPLIT START***********\n");
	while (argv && argv[i])
	{
		ft_putstr_fd("!", 2);
		ft_putstr_fd(argv[i], 2);
		ft_putstr_fd("!", 2);
		i++;
	}
	printf("\n**********SPLIT END***********\n");
}

void	free_list(t_list *list)
{
	t_node	*tmp;

	while (list && list->head)
	{
		if (list->head->basic_command)
			free(list->head->basic_command);
		if (list->head->splited_command)
			free_split(list->head->splited_command);
		if (list->head->args)
			free_split(list->head->args);
		tmp = list->head->next;
		free(list->head);
		list->head = tmp;
	}
	if (list)
		free(list);
}

void	print_list(t_list *arg)
{
	t_node	*tmp;

	tmp = arg->head;
	while (tmp)
	{
		ft_putstr_fd("Basic Command: \n", 2);
		ft_putstr_fd(tmp->basic_command, 2);
		ft_putstr_fd("\nHAS PIPE: \n", 2);
		ft_putnbr_fd(tmp->has_pipe, 2);
		ft_putstr_fd("\n", 2);
		tmp = tmp->next;
	}
}
