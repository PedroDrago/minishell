#include "../includes/minishell.h"

int	validate_splited_command(char **splited_command)
{
	int	i;

	i = 0;
	while(splited_command[i])
	{
		if (is_pipe(splited_command[i]))
			break ;
		if (is_token(splited_command[i]))
		{
			if (!splited_command[i + 1])
				return (ft_putstr_fd("Minishell: Syntax error [Unresolved Token]\n", 2), FALSE);
			else if (is_token(splited_command[i + 1]))
				return (ft_putstr_fd("Minishell: Syntax error [Double Token]\n", 2), FALSE);
		}
		i++;
	}
	return (TRUE);
}
int	validate_list(t_list *list)
{
	t_node *tmp;
	char	**splited_command;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->has_pipe && !tmp->next)
			return (ft_putstr_fd("Minishell: Syntax error [void pipe]\n", 2), FALSE);
		splited_command = command_split(tmp->basic_command);
		if (!validate_splited_command(splited_command))
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}
