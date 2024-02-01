/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:29:15 by pdrago            #+#    #+#             */
/*   Updated: 2024/02/01 16:29:16 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_file(int fd)
{
	char	*tmp;
	char	*str;

	str = (char *) malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	tmp = get_next_line(fd);
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		str = ft_strjoin(str, tmp, 1);
		free (tmp);
		tmp = get_next_line(fd);
	}
	return (str);
}

long	copy_final_line(char *str, char *tmp, int start)
{
	int	count;

	count = 0;
	while (str[++start])
	{
		tmp[count] = str[start];
		count++;
	}
	tmp[count] = '\0';
	return (ft_atoi(tmp));
}

long	get_history_count(int fd)
{
	int		start;
	int		end;
	int		history_count;
	char	*str;
	char	*tmp;

	start = 0;
	end = 0;
	str = read_file(fd);
	if (!str)
		return (-1);
	while (str[end])
		end++;
	start = end - 1;
	while (str[--start] != '\n')
		;
	tmp = malloc(sizeof(char) * (end - start + 2));
	if (!tmp)
		return (-1);
	history_count = copy_final_line(str, tmp, start);
	return (free(tmp), free(str), history_count);
}

int	register_command(char *prompt, int fd)
{
	static long	history_count;
	char		*number_string;
	struct stat	status;

	fstat(fd, &status);
	if (!history_count)
	{
		if (status.st_size == 0)
			history_count = 0;
		else
		{
			history_count = get_history_count(fd);
			if (history_count < 0)
				return (-1);
		}
	}
	history_count++;
	number_string = ft_itoa(history_count);
	write(fd, number_string, ft_strlen(number_string));
	write(fd, " ", 1);
	write(fd, prompt, ft_strlen(prompt));
	write(fd, "\n", 1);
	return (free(number_string), history_count);
}
