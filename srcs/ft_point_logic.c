/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette < wlanette@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:06:03 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/22 21:05:30 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_file_struct.h"
#include "BSQ.h"

t_point	*create_point(int x, int y)
{
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (point == 0)
		return (0);
	point->x = x;
	point->y = y;
	return (point);
}

t_point_list	*push_point(t_point_list *point_list, t_point *point)
{
	t_point_list	*new_point_list;

	new_point_list = malloc(sizeof(t_point_list));
	new_point_list->point = point;
	new_point_list->next = point_list;
	return (new_point_list);
}

t_point_list	*copy_point_list(t_point_list *old_point_list)
{
	t_point_list	*new_point_list;
	t_point_list	*temp_point_list;

	if (old_point_list == 0)
		return (0);
	new_point_list = 0;
	temp_point_list = old_point_list;
	while (temp_point_list != 0)
	{
		new_point_list = push_point(new_point_list, temp_point_list->point);
		temp_point_list = temp_point_list->next;
	}
	return (new_point_list);
}

void	free_point_list(t_point_list *point_list)
{
	if (point_list == 0)
		return ;
	if (point_list->next == 0)
	{
		free(point_list);
		return ;
	}
	else
	{
		free_point_list(point_list->next);
		free(point_list);
		return ;
	}
}
