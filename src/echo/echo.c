#include "../../includes/minishell.h"

int	main(int argc, char *argv[])
{
	int	flag;
	int	count;

	flag = 0;
	count = 0;
	if (argc > 0 && argv[0][0] == '-')
	{
		if (!ft_strncmp(argv[0], "-n", 3))
		{
			flag = 1;
			count++;
		}
	}

	while (argv[count])
	{
		printf("%s", argv[count]);
		if (count != (argc - 1))
			printf(" ");
		count++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
