/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_borders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette < wlanette@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:15:06 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/22 21:12:43 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_file_struct.h"
#include "BSQ.h"

int	check_top_border_rules(t_rect *rect)
{
	t_point_list	*temp_point_list;
	t_point_list	*last_ok_point_list;
	t_point_list	*to_remove_point_list;

	if (rect->point_list_top == 0)
		return (1);
	last_ok_point_list = 0;
	to_remove_point_list = 0;
	temp_point_list = rect->point_list_top;
	while (temp_point_list != 0)
	{
		if (temp_point_list->point->y >= rect->top_left->y && \
			temp_point_list->point->y <= rect->bot_right->y)
			last_ok_point_list = push_point(last_ok_point_list, \
				temp_point_list->point);
		else
			to_remove_point_list = push_point(to_remove_point_list, \
				temp_point_list->point);
		temp_point_list = temp_point_list->next;
	}
	if (last_ok_point_list == 0)
		return (0);
	rect->point_list_top = last_ok_point_list;
	free_point_list(to_remove_point_list);
	return (1);
}

int	check_bot_border_rules(t_rect *rect)
{
	t_point_list	*temp_point_list;
	t_point_list	*last_ok_point_list;
	t_point_list	*to_remove_point_list;

	if (rect->point_list_bot == 0)
		return (1);
	last_ok_point_list = 0;
	to_remove_point_list = 0;
	temp_point_list = rect->point_list_bot;
	while (temp_point_list != 0)
	{
		if (temp_point_list->point->y >= rect->top_left->y && \
			temp_point_list->point->y <= rect->bot_right->y)
			last_ok_point_list = push_point(last_ok_point_list, \
				temp_point_list->point);
		else
			to_remove_point_list = push_point(to_remove_point_list, \
				temp_point_list->point);
		temp_point_list = temp_point_list->next;
	}
	if (last_ok_point_list == 0)
		return (0);
	rect->point_list_bot = last_ok_point_list;
	free_point_list(to_remove_point_list);
	return (1);
}

int	check_left_border_rules(t_rect *rect)
{
	t_point_list	*temp_point_list;
	t_point_list	*last_ok_point_list;
	t_point_list	*to_remove_point_list;

	if (rect->point_list_left == 0)
		return (1);
	last_ok_point_list = 0;
	to_remove_point_list = 0;
	temp_point_list = rect->point_list_left;
	while (temp_point_list != 0)
	{
		if (temp_point_list->point->x >= rect->top_left->x && \
			temp_point_list->point->x <= rect->bot_right->x)
			last_ok_point_list = push_point(last_ok_point_list, \
				temp_point_list->point);
		else
			to_remove_point_list = push_point(to_remove_point_list, \
				temp_point_list->point);
		temp_point_list = temp_point_list->next;
	}
	if (last_ok_point_list == 0)
		return (0);
	rect->point_list_left = last_ok_point_list;
	free_point_list(to_remove_point_list);
	return (1);
}

int	check_right_border_rules(t_rect *rect)
{
	t_point_list	*temp_point_list;
	t_point_list	*last_ok_point_list;
	t_point_list	*to_remove_point_list;

	if (rect->point_list_right == 0)
		return (1);
	last_ok_point_list = 0;
	to_remove_point_list = 0;
	temp_point_list = rect->point_list_right;
	while (temp_point_list != 0)
	{
		if (temp_point_list->point->x >= rect->top_left->x && \
			temp_point_list->point->x <= rect->bot_right->x)
			last_ok_point_list = push_point(last_ok_point_list, \
				temp_point_list->point);
		else
			to_remove_point_list = push_point(to_remove_point_list, \
				temp_point_list->point);
		temp_point_list = temp_point_list->next;
	}
	if (last_ok_point_list == 0)
		return (0);
	rect->point_list_right = last_ok_point_list;
	free_point_list(to_remove_point_list);
	return (1);
}
