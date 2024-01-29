/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:45:11 by pdrago            #+#    #+#             */
/*   Updated: 2023/11/16 23:12:02 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*dup_pre_n(char *buffer)
{
	int		count;
	int		flag;
	int		count2;
	char	*pre_n;

	count = 0;
	flag = 0;
	while (buffer[count] && buffer[count] != '\n')
		count++;
	if (buffer[count] == '\n')
		flag++;
	pre_n = (char *) malloc (sizeof(char) * count + flag + 1);
	if (!pre_n)
		return (NULL);
	count2 = 0;
	while (count2 < count)
	{
		pre_n[count2] = buffer[count2];
		count2++;
	}
	if (buffer[count] == '\n')
		pre_n[count++] = '\n';
	pre_n[count] = '\0';
	return (pre_n);
}

char	*dup_post_n(char *buffer)
{
	int		count;
	int		count2;
	char	*post_n;

	count = 0;
	count2 = 0;
	while (buffer[count] && buffer[count] != '\n')
		count++;
	if (!buffer[count])
	{
		free (buffer);
		return (NULL);
	}
	count++;
	post_n = (char *) malloc (sizeof(char) * (gnl_len(buffer) - count) + 1);
	if (!post_n)
		return (NULL);
	while (buffer[count + count2])
	{
		post_n[count2] = buffer[count + count2];
		count2++;
	}
	post_n[count2] = '\0';
	free (buffer);
	return (post_n);
}

char	*read_line(int fd)
{
	static char	*hold[MAX_FD];
	char		*buffer;
	int			bytes;

	buffer = (char *) malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && !has_break_line(hold[fd]))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free (buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		hold[fd] = ft_joinfree(hold[fd], buffer);
	}
	free (buffer);
	if (!hold[fd])
		return (NULL);
	buffer = dup_pre_n(hold[fd]);
	hold[fd] = dup_post_n(hold[fd]);
	return (buffer);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	return (read_line(fd));
}
