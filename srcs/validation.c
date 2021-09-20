/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qagda <qagda@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:58:08 by qagda             #+#    #+#             */
/*   Updated: 2021/09/20 23:58:10 by qagda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BSQ.h"
#include "ft_file_struct.h"

#include <stdio.h>

t_bool	ft_is_not_valid(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\v' || c == '\r' || c == '\f' || c == '\0');
}

t_bool	ft_is_map_valid(char *file)
{
	int	etalon;
	int	index;

	index = 0;
	while (!ft_is_not_valid(*file))
	{
		if (ft_strlen(file) < 5)
			return (false);
		file++;
	}
	if (*file != '\0')
	{
		file++;
		etalon = ft_strlen(file);
		if (etalon == 0)
			return (false);
		while (*file != '\0')
		{
			if (etalon != ft_strlen(file))
				return (false);
			file += etalon + 1;
		}
		return (true);
	}
	return (false);
}

t_bool	ft_is_one_line(char *file)
{
	int	index;
	int	curr_strs_len;

	index = 0;
	curr_strs_len = 0;
	while (file[index] != '\0')
	{
		if (file[index] == '\n')
			curr_strs_len++;
		if (curr_strs_len >= 2)
			return (true);
		index++;
	}
	return (false);
}
