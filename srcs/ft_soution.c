/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_soution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette < wlanette@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:13:27 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/22 21:03:07 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_file_struct.h"
#include "BSQ.h"

t_rect_list	*get_rect_cands(t_rect *rect, t_point *obs,
	t_rect_list *new_rect_list)
{
	int			delta_left;
	int			delta_right;
	int			delta_top;
	int			delta_bot;

	delta_left = obs->y - rect->top_left->y;
	delta_right = rect->bot_right->y - obs->y;
	delta_top = obs->x - rect->top_left->x;
	delta_bot = rect->bot_right->x - obs->x;
	if (delta_left < 0 || delta_right < 0 || delta_top < 0 || delta_bot < 0)
	{
		new_rect_list = push_rect(new_rect_list, rect);
		return (new_rect_list);
	}
	if (delta_left > 0)
		new_rect_list = push_rect(new_rect_list, get_left_rect(rect, obs));
	if (delta_right > 0)
		new_rect_list = push_rect(new_rect_list, get_right_rect(rect, obs));
	if (delta_top > 0)
		new_rect_list = push_rect(new_rect_list, get_top_rect(rect, obs));
	if (delta_bot > 0)
		new_rect_list = push_rect(new_rect_list, get_bot_rect(rect, obs));
	free_rect(rect);
	return (new_rect_list);
}

t_rect_list	*get_rects_list(t_point_list *obs_list, int n, int m)
{
	t_rect_list		*full_rect_list;
	t_rect_list		*new_rect_list;
	t_rect_list		*temp_rect_list;
	t_point_list	*temp_obs_list;

	full_rect_list = 0;
	new_rect_list = 0;
	full_rect_list = push_rect(full_rect_list, \
				create_rect(create_point(0, 0), create_point(n - 1, m - 1)));
	temp_obs_list = obs_list;
	while (temp_obs_list != 0)
	{
		temp_rect_list = full_rect_list;
		while (temp_rect_list != 0)
		{
			new_rect_list = get_rect_cands(temp_rect_list->rect, \
				temp_obs_list->point, new_rect_list);
			temp_rect_list = temp_rect_list->next;
		}
		free_rect_list(full_rect_list);
		full_rect_list = new_rect_list;
		new_rect_list = 0;
		temp_obs_list = temp_obs_list->next;
	}
	return (full_rect_list);
}

t_rect	*get_max_rect(t_rect_list *rect_list)
{
	t_rect			*max_rect;
	t_rect_list		*temp_rect_list;
	int				max_size;
	int				cur_size;

	max_rect = rect_list->rect;
	max_size = ft_min(rect_list->rect->bot_right->x \
					- rect_list->rect->top_left->x, \
					rect_list->rect->bot_right->y \
					- rect_list->rect->top_left->y);
	temp_rect_list = rect_list;
	while (temp_rect_list != 0)
	{
		cur_size = ft_min(temp_rect_list->rect->bot_right->x \
		- temp_rect_list->rect->top_left->x, \
			temp_rect_list->rect->bot_right->y \
			- temp_rect_list->rect->top_left->y);
		if (max_size < cur_size)
		{
			max_rect = temp_rect_list->rect;
			max_size = cur_size;
		}
		temp_rect_list = temp_rect_list -> next;
	}
	return (max_rect);
}

int	**fill_square_2d_int_arr(int **arr, t_rect *rect, int value)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = ft_min(rect->bot_right->x - rect->top_left->x, \
		rect->bot_right->y - rect->top_left->y);
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			arr[rect->top_left->x + i][rect->top_left->y + j] = value;
			j++;
		}
		i++;
	}
	return (arr);
}
