#include "../includes/minishell.h"

void	exit_program(int sig)
{
	static int	process = 0;

	if (sig == SIGUSR2)
		process = 1;
	if (sig == SIGUSR1)
		process = 0;
	g_sig = sig;
	if (g_sig == SIGINT)
	{
		if (!process)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
}

void	free_before_safely_exit(t_shell *shell)
{
	free_process_data(shell);
	free(shell->prompt_string);
	free_env(shell->env);
	free(shell);
	rl_clear_history();
}

void	exit_safely(t_shell *shell, unsigned char status)
{
	free(shell->prompt_string);
	free_env(shell->env);
	free(shell);
	rl_clear_history();
	exit(status);
}

long long int	ft_atolli_mod(const char *nptr)
{
	long long int	total;
	long long int	signal;

	total = 0;
	signal = 1;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if ((*nptr == '-' || *nptr == '+') && *nptr++ == '-')
		signal *= -1;
	while (ft_isdigit(*nptr))
		total = total * 10 + (*nptr++ - '0');
	return (total * signal);
}

int	is_valid_lli(char *status)
{
	unsigned long long int	total;
	unsigned long long int	max_lli;
	int						signal;

	max_lli = 9223372036854775808ULL;
	total = 0;
	signal = 1;
	if (!status)
		return (0);
	while ((*status >= '\t' && *status <= '\r') || *status == ' ')
		status++;
	if (*status == '-' || *status == '+')
		if (*status++ == '-')
			signal *= -1;
	if (ft_strlen(status) > 19)
		return (0);
	while (ft_isdigit(*status) && total < max_lli)
		total = total * 10 + (*status++ - '0');
	if (total > max_lli)
		return (0);
	if (total == max_lli && signal == 1)
		return (0);
	return (1);
}

int	is_numeric_argument(char *str)
{
	int	space_flag;

	if (!str)
		return (0);
	space_flag = 0;
	while (*str && *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			if (*str == ' ')
				space_flag++;
			else
				return (0);
		}
		else
			if (space_flag && ft_isdigit(*str))
				return (0);
		str++;
	}
	return (1);
}

void	builtin_exit(t_shell *shell, t_node *node)
{
	int		len;
	int		is_numeric;

	len = split_len(node->args);
	ft_putstr_fd("exit\n", 1);
	if (len == 1)
		exit_safely(shell, 0);
	is_numeric = is_numeric_argument(node->args[1]);
	if (len == 2 && is_numeric)
		if (is_valid_lli(node->args[1]))
			exit_safely(shell, ft_atolli_mod(node->args[1]));
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(node->args[1], 2);
	if (len == 2 && (!is_numeric || !is_valid_lli(node->args[1])))
	{
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_safely(shell, 2);
	}
	if (!is_numeric)
	{
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_safely(shell, 156);
	}
	ft_putstr_fd(": too many arguments\n", 2);
	exit_safely(shell, 1);
}
