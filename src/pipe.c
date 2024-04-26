#include "../includes/minishell.h"

int	setup_list_pipes(t_list *list)
{
	t_node	*tmp;
	int		pipe_fd[2];

	tmp = list->head;
	while (tmp)
	{
		if (tmp->has_pipe)
		{
			pipe(pipe_fd);
			tmp->node_pipe[1] = pipe_fd[1];
			tmp->next->node_pipe[0] = pipe_fd[0]; //WARN: Needs previous validation so that tmp->next won't be NULL;
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

int	is_token(char *str)
{
	if (!ft_strncmp(str, "<", 2))
		return (TRUE);
	if (!ft_strncmp(str, "<<", 3))
		return (TRUE);
	if (!ft_strncmp(str, ">>", 3))
		return (TRUE);
	if (!ft_strncmp(str, ">", 2))
		return (TRUE);
	if (!ft_strncmp(str, "|", 2))
		return (TRUE);
	return (FALSE);
}

int	is_pipe(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (TRUE);
	return (FALSE);
}
