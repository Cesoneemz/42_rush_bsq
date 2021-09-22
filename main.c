/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette < wlanette@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:22:49 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/22 20:24:46 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "BSQ.h"
#include "ft_file_struct.h"

#include <stdio.h>
#include <unistd.h>

int **get_filled_field(int **field, t_point_list *obs_list, t_matrix map_info)
{
	t_rect_list		*rect_list;
	t_rect			*max_rect;
	int				index;
	int				jndex;

	index = 0;
	while (index < map_info.strs_len)
	{
		jndex = 0;
		while (jndex < map_info.strlen)
		{
			if (field[index][jndex] == 1)
				obs_list = push_point(obs_list, create_point(index, jndex));
			jndex++;
		}
		index++;
	}
	if (obs_list == NULL)
		return (NULL);
	rect_list = get_rects_list(obs_list, map_info.strs_len, map_info.strlen);
	if (rect_list == NULL)
		return (NULL);
	max_rect = get_max_rect(rect_list);
	field = fill_square_2d_int_arr(field, max_rect, 2);
	index = 0;
	while (index < map_info.strs_len)
	{
		jndex = 0;
		while (jndex < map_info.strlen)
		{
			if (field[index][jndex] == 1)
				field[index][jndex] = map_info.obtacle_sym;
			if (field[index][jndex] == 0)
				field[index][jndex] = map_info.empty_sym;
			if (field[index][jndex] == 2)
				field[index][jndex] = map_info.fill_sym;
			jndex++;
		}
		index++;
	}
	free_full_rect_list(rect_list);
	return (field);
}

void	print_2d_int_arr(int **arr, int n, int m)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < m)
		{
			ft_putchar(arr[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int main(int argc, char **argv)
{
	int 			**field;
	int				**matrix;
	t_point_list	*obs_list;
	char			*file;
	t_matrix		map_info;

	if (argc > 2)
		return (0);
	obs_list = NULL;
	file = ft_load_file(argv[1]);
	map_info = ft_get_map_info(file);
	field = ft_parse_map(file, map_info);
	matrix = get_filled_field(field, obs_list, map_info);
	if (matrix == NULL)
		return (0);
	else
		print_2d_int_arr(matrix, map_info.strs_len, map_info.strlen);
		return (0);
	return (0);
}

