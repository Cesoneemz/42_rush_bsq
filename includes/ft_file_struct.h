/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette < wlanette@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:05:36 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/22 20:49:42 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_STRUCT_H
# define FT_FILE_STRUCT_H

typedef struct s_matrix
{
	int		strs_len;
	int		strlen;
	char	empty_sym;
	char	obtacle_sym;
	char	fill_sym;

}			t_matrix;

typedef enum s_bool
{
	false = 0,
	true = 1
}			t_bool;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_point_list
{
	t_point				*point;
	struct s_point_list	*next;
}						t_point_list;

typedef struct s_rect
{
	t_point			*top_left;
	t_point			*bot_right;
	t_point_list	*point_list_left;
	t_point_list	*point_list_right;
	t_point_list	*point_list_top;
	t_point_list	*point_list_bot;
}					t_rect;

typedef struct s_rect_list
{
	t_rect				*rect;
	struct s_rect_list	*next;
}						t_rect_list;

#endif
