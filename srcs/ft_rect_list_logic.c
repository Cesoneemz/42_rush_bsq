/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rect_list_logic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette < wlanette@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:10:34 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/22 21:04:13 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_file_struct.h"
#include "BSQ.h"

t_rect_list	*push_rect(t_rect_list *rect_list, t_rect *rect)
{
	t_rect_list	*new_rect_list;

	if (rect == 0)
		return (rect_list);
	new_rect_list = malloc(sizeof(t_rect_list));
	new_rect_list->rect = rect;
	new_rect_list->next = rect_list;
	return (new_rect_list);
}

void	free_rect(t_rect *rect)
{
	free_point_list(rect->point_list_left);
	free_point_list(rect->point_list_right);
	free_point_list(rect->point_list_top);
	free_point_list(rect->point_list_bot);
	free(rect->top_left);
	free(rect->bot_right);
	free(rect);
}

void	free_rect_list(t_rect_list *rect_list)
{
	if (rect_list == 0)
		return ;
	if (rect_list->next == 0)
	{
		free(rect_list);
		return ;
	}
	else
	{
		free_rect_list(rect_list->next);
		free(rect_list);
		return ;
	}
}

void	free_full_rect_list(t_rect_list *rect_list)
{
	t_rect_list	*temp_rect_list;

	temp_rect_list = rect_list;
	while (temp_rect_list != 0)
	{
		free_rect(temp_rect_list->rect);
		temp_rect_list = temp_rect_list ->next;
	}
	free_rect_list(rect_list);
}
