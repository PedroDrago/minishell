#include "../includes/minishell.h"

int	validate_characters(char *prompt)
{
	int				i;
	t_validation	flags;

	init_flags(&flags, &i);
	while (prompt[++i])
	{
		resolve_quotes(prompt[i], &flags.in_single_quotes,
			&flags.in_double_quotes);
		if (!flags.in_single_quotes && !flags.in_double_quotes)
		{
			if (prompt[i] == ';' || prompt[i] == '\\')
			{
				ft_putstr_fd("Minishell: syntax error: Invalid character:`", 2),
				ft_putchar_fd(prompt[i], 2);
				ft_putstr_fd("'\n", 2);
				return (FALSE);
			}
		}
	}
	return (TRUE);
}
