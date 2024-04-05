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
int	validate_list(t_shell *shell, t_list *list) // return status de void pipe
{
	t_node *tmp;
	char	**splited_command;
	tmp = list->head;
	while (tmp)
	{
		if (tmp->has_pipe && !tmp->next)
		{
			set_exit_status(2, shell);
			return (ft_putstr_fd("Minishell: Syntax error [void pipe]\n", 2), FALSE);
		}
		splited_command = command_split(tmp->basic_command);
		if (!validate_splited_command(splited_command))
		{
			set_exit_status(2, shell);
			return ( free_split(splited_command), FALSE);
		}
		free_split(splited_command);
		tmp = tmp->next;
	}
	return (TRUE);
}

/*
echo >>        >cat
Minishell: Syntax error [Double Token]
rafaelro:/nfs/homes/rafaelro/Documents/ms03212024$ echo >>        >>cat
Minishell: Syntax error [Double Token]
rafaelro:/nfs/homes/rafaelro/Documents/ms03212024$ echo >>        > cat
Minishell: Syntax error [Double Token]
rafaelro:/nfs/homes/rafaelro/Documents/ms03212024$ echo >>        | cat
*/