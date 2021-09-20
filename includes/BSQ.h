/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BSQ.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qagda <qagda@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:12:32 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/20 23:55:58 by qagda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include "ft_file_struct.h"

int			ft_strlen(char *str);
char		*ft_load_file(char *path);
t_matrix	ft_get_map_info(char *file);
int			**ft_parse_map(char *file, t_matrix map_info);
int			ft_strlen(char *str);
t_bool		ft_is_map_valid(char *file);
t_bool		ft_is_one_line(char *file);

#endif
