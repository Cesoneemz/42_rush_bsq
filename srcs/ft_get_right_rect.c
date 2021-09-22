/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_right_rect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette < wlanette@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:19:42 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/22 21:09:14 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_file_struct.h"
#include "BSQ.h"

t_rect	*get_left_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_left;
	t_point	*bot_right;

	bot_right = create_point(rect->bot_right->x, obs->y - 1);
	rect_left = inherit_rect(rect->top_left, bot_right, rect);
	free(bot_right);
	rect_left->point_list_right = 0;
	rect_left->point_list_right = push_point(rect_left->point_list_right, obs);
	if (check_left_border_rules(rect_left) && \
		check_right_border_rules(rect_left) && \
		check_top_border_rules(rect_left) && \
		check_bot_border_rules(rect_left))
		return (rect_left);
	else
		return (0);
}

t_rect	*get_right_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_right;
	t_point	*top_left;

	top_left = create_point(rect->top_left->x, obs->y + 1);
	rect_right = inherit_rect(top_left, rect->bot_right, rect);
	free(top_left);
	rect_right->point_list_left = 0;
	rect_right->point_list_left = push_point(rect_right->point_list_left, obs);
	if (check_left_border_rules(rect_right) && \
		check_right_border_rules(rect_right) && \
		check_top_border_rules(rect_right) && \
		check_bot_border_rules(rect_right))
		return (rect_right);
	else
		return (0);
}

t_rect	*get_top_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_top;
	t_point	*bot_right;

	bot_right = create_point(obs->x - 1, rect->bot_right->y);
	rect_top = inherit_rect(rect->top_left, bot_right, rect);
	free(bot_right);
	rect_top->point_list_bot = 0;
	rect_top->point_list_bot = push_point(rect_top->point_list_bot, obs);
	if (check_left_border_rules(rect_top) && \
		check_right_border_rules(rect_top) && \
		check_top_border_rules(rect_top) && \
		check_bot_border_rules(rect_top))
		return (rect_top);
	else
		return (0);
}

t_rect	*get_bot_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_bot;
	t_point	*top_left;

	top_left = create_point(obs->x + 1, rect->top_left->y);
	rect_bot = inherit_rect(top_left, rect->bot_right, rect);
	free(top_left);
	rect_bot->point_list_top = 0;
	rect_bot->point_list_top = push_point(rect_bot->point_list_top, obs);
	if (check_left_border_rules(rect_bot) && \
		check_right_border_rules(rect_bot) && \
		check_top_border_rules(rect_bot) && \
		check_bot_border_rules(rect_bot))
		return (rect_bot);
	else
		return (0);
}
