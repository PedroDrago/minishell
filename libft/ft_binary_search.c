/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:56:02 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/07 00:01:34 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_binary_search(int size, int array[], int wanted)
{
	int	index;
	int	start;
	int	end;

	start = 0;
	end = size - 1;
	while (start <= end)
	{
		index = start + ((end - start) / 2);
		if (array[index] == wanted)
			return (index);
		else
		{
			if (array[index] > wanted)
				end = index - 1;
			else
				start = index + 1;
		}
	}
	return (-1);
}
