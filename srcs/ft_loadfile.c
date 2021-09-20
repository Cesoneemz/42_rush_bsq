/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loadfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qagda <qagda@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:55:48 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/20 22:39:59 by qagda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "ft_file_struct.h"
#include "BSQ.h"

#define BUF_SIZE 2048

char	*ft_load_file(char *path)
{
	int		fd;
	char	*byte;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	byte = (char *)malloc(BUF_SIZE);
	if (!byte)
		return (NULL);
	i = 0;
	while ((read(fd, &byte[i], 1)))
		i++;
	return (byte);
}

t_matrix	ft_get_map_info(char *file)
{
	t_matrix	map_info;

	map_info.strs_len = file[0] - '0';
	map_info.strlen = ft_strlen(file + 5);
	map_info.empty_sym = file[1];
	map_info.obtacle_sym = file[2];
	map_info.fill_sym = file[3];
	return (map_info);
}

int	**ft_parse_map(char *file, t_matrix map)
{
	int		**matrix;
	int		index;
	int		jndex;

	matrix = (int **)malloc(map.strs_len * map.strlen * sizeof(int *));
	if (matrix == NULL)
		return (NULL);
	index = 0;
	file += 5;
	while (index < map.strs_len)
	{
		jndex = 0;
		matrix[index] = (int *)malloc(map.strlen * sizeof(int));
		while (jndex < map.strlen)
		{
			if (*file == map.empty_sym)
				matrix[index][jndex] = 0;
			if (*file == map.obtacle_sym)
				matrix[index][jndex] = 1;
			jndex++;
			file++;
		}
		index++;
	}
	return (matrix);
}
