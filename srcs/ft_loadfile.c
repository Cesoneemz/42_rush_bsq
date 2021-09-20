/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loadfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:55:48 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/20 19:55:48 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "ft_file_struct.h"
#include "BSQ.h"

# define BUF_SIZE 2048

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

int			**ft_parse_map(char *file, t_matrix map_info)
{
	int		**matrix;
	int		index;
	int		jndex;

	matrix = (int **)malloc(map_info.strs_len * map_info.strlen * sizeof(int *));
	if (matrix == NULL)
		return (NULL);
	index = 1;
	file += 5;
	while (index < map_info.strs_len + 1)
	{
		jndex = 0;
		matrix[index] = (int *)malloc(map_info.strlen * sizeof(int));
		while (jndex < map_info.strlen && *file != '\n')
		{
			if (*file == map_info.empty_sym)
				matrix[index][jndex] = 0;
			if (*file == map_info.obtacle_sym)
				matrix[index][jndex] = 1;
			printf("%d", matrix[index][jndex]);
			jndex++;
			file++;
		}
		printf("\n");
		file++;
		index++;
	}
	return (matrix);
}
