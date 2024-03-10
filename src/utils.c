#include "../includes/minishell.h"

void	free_split(char **splited)
{
	int	count;

	count = -1;
	while (splited[++count])
		free(splited[count]);
	free(splited);
}

void	print_split(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		printf("%s|", argv[i++]);
	printf("\n");
}

void	print_list(t_list *arg)
{
	t_node *tmp;

	tmp = arg->head;
	while (tmp)
	{
		printf("command: %s\n", tmp->command);
		printf("args: ");
		print_split(tmp->args);
		printf("token: %s\n", tmp->token);
		tmp = tmp->next;
	}
}
