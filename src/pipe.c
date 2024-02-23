#include "../includes/minishell.h"
#include <unistd.h>

int *evaluate_command(t_node *current, int *fds)
{
	char *path;
	int pid;
	int *yield;

	yield = (int *) malloc(sizeof(int) * 2);
	pipe(yield);
	pid = fork();
	if (pid == 0)
	{
		dup2(fds[0], 0);
		dup2(yield[1], 1);
		close(fds[0]);
		close(fds[1]);
		close(yield[1]);
		path = ft_strjoin("/bin/", current->command, O_NONE);
		execv(path, current->args);
	}
	else
	{
		close(fds[1]);
		close(fds[0]);
		waitpid(pid, NULL, 0);
	}
	return (yield);
}

int    evaluate_prompt(char *prompt, t_shell *shell)
{
	t_list    *prompt_list;
	t_node	*current;
	int *yield;

	prompt_list = generate_list(prompt);
	if (!prompt_list)
		return (FALSE);
	current = prompt_list->head;
	yield = (int *) malloc (sizeof(int) * 2);
	pipe(yield);
	while (current)
	{
		yield = evaluate_command(current, yield);
		current = current->next;
	}
	//isso aqui abaixo foi apenas para testar se o output tava certo
	char *buffer = malloc(sizeof(char) * 500);
	int b = read(yield[0], buffer,  500);
	buffer[b] = '\0';
	printf("%s", buffer); //se tentar fazer write(1, &buffer, ft_strlen(buffer)) vai dar errado n sei pq, e se tentar ler com a GNL vai travar pelo visto o motivo do travamento é fds que n foram fechados
	(void) shell;
	return (TRUE);
}
