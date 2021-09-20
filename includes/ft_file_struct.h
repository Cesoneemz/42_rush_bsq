/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qagda <qagda@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:05:36 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/20 22:48:24 by qagda            ###   ########.fr       */
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

#endif
