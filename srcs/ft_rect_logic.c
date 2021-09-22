/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rect_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette < wlanette@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:08:05 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/22 21:03:37 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_file_struct.h"
#include "BSQ.h"

t_rect	*create_rect(t_point *top_left, t_point *bot_right)
{
	t_rect	*rect;

	rect = malloc(sizeof(t_rect));
	if (rect == 0)
		return (0);
	rect->point_list_left = 0;
	rect->point_list_right = 0;
	rect->point_list_top = 0;
	rect->point_list_bot = 0;
	rect->top_left = create_point(top_left->x, top_left->y);
	rect->bot_right = create_point(bot_right->x, bot_right->y);
	return (rect);
}

t_rect	*inherit_rect(t_point *top_left, t_point *bot_right, t_rect *base_rect)
{
	t_rect	*rect;

	rect = create_rect(top_left, bot_right);
	rect->point_list_left = copy_point_list(base_rect->point_list_left);
	rect->point_list_right = copy_point_list(base_rect->point_list_right);
	rect->point_list_top = copy_point_list(base_rect->point_list_top);
	rect->point_list_bot = copy_point_list(base_rect->point_list_bot);
	return (rect);
}
