/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qagda <qagda@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:22:49 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/20 23:29:19 by qagda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "BSQ.h"
#include "ft_file_struct.h"

#include <stdio.h>

int main(int argc, char **argv)
{
	char		*file;
	t_matrix	map_info;
	int			**matrix;

	if (argc > 2)
		return (0);
	file = ft_load_file(argv[1]);
	if (ft_is_map_valid(file) && ft_is_one_line(file))
	{
		printf("Hi");
		map_info = ft_get_map_info(file);
		matrix = ft_parse_map(file, map_info);
	}
	else
		printf("Hiiiiiiiiiii");

	return (0);
}

