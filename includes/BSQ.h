/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BSQ.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette < wlanette@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:12:32 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/22 20:49:20 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include "ft_file_struct.h"

int				ft_strlen(char *str);
char			*ft_load_file(char *path);
t_matrix		ft_get_map_info(char *file);
int				**ft_parse_map(char *file, t_matrix map_info);
int				ft_strlen(char *str);
t_bool			ft_is_map_valid(char *file);
t_bool			ft_is_one_line(char *file);
t_rect			*get_max_rect(t_rect_list *rect_list);
t_rect_list		*get_rects_list(t_point_list *obs_list, int n, int m);
int				**fill_square_2d_int_arr(int **arr, t_rect *rect, int value);
void			free_full_rect_list(t_rect_list *rect_list);
void			free_point_list(t_point_list *point_list);
t_point_list	*push_point(t_point_list *point_list, t_point *point);
t_point			*create_point(int x, int y);
t_point_list	*copy_point_list(t_point_list *old_point_list);
t_rect			*create_rect(t_point *top_left, t_point *bot_right);
t_rect			*inherit_rect(t_point *top_left, t_point *bot_right, \
												t_rect *base_rect);
t_rect_list		*push_rect(t_rect_list *rect_list, t_rect *rect);
int				ft_min(int a, int b);
void			free_rect_list(t_rect_list *rect_list);
void			free_rect(t_rect *rect);
int				check_top_border_rules(t_rect *rect);
int				check_bot_border_rules(t_rect *rect);
int				check_left_border_rules(t_rect *rect);
int				check_right_border_rules(t_rect *rect);
t_rect			*get_left_rect(t_rect *rect, t_point *obs);
t_rect			*get_right_rect(t_rect *rect, t_point *obs);
t_rect			*get_top_rect(t_rect *rect, t_point *obs);
t_rect			*get_bot_rect(t_rect *rect, t_point *obs);
void			ft_putchar(char c);
t_bool			ft_is_not_valid(char c);

#endif
