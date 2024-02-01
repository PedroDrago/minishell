#include "../includes/minishell.h"
#include <sys/stat.h>


int main(void)
{
	char	*prompt;
	int	history_fd;

	history_fd = open("history", O_RDWR | O_APPEND | O_CREAT, 0777);
	while (TRUE)
	{
		prompt = readline("$ ");
		if (register_command(prompt, history_fd) < 0)
			return (1);
	}
	(void) history_fd;
	(void) prompt;
}
