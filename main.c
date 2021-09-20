/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:22:49 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/20 20:22:49 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "BSQ.h"
#include "ft_file_struct.h"

int main(int argc, char **argv)
{
	char		*file;
	t_matrix	map_info;
	int			**matrix;
	
	
	if (argc > 2)
		return (0);
	file = ft_load_file(argv[1]);
	map_info = ft_get_map_info(file);
	matrix = ft_parse_map(file, map_info);
	for (int i = 0; i < map_info.strs_len; i++)
	{
		for (int j = 0; i < map_info.strlen; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}
