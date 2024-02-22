#include "../includes/minishell.h"

void	free_split(char **splited)
{
	int	count;

	count = -1;
	while (splited[++count])
		free(splited[count]);
	free (splited);
}

void	print_split(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		printf("%s \n", argv[i++]);
}

void	print_list(t_list *arg)
{
	t_list	*list;

	list = arg;
	while (list->head)
	{
		printf("command: %s\n", list->head->command);
		printf("args: ");
		print_split(list->head->args);
		printf("token: %s\n", list->head->token);
		list->head = list->head->next;
	}
}
