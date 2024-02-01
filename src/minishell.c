#include "../includes/minishell.h"

int main(void)
{
	char	*prompt;
	while (TRUE)
	{
		prompt = readline("$ ");
	}
	(void) prompt;
}
