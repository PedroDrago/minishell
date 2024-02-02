#include "../../includes/minishell.h"

int	main(void)
{
	char	*buffer;
	int	size;

	size = 100;
	buffer = (char *) malloc(sizeof(char) * size);
	while(!getcwd(buffer, size))
	{
		free(buffer);
		size += 100;
		buffer = (char *) malloc(sizeof(char) * size);
	}
	printf("%s\n", buffer);
	free(buffer);
}
