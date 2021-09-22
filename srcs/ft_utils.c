/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette < wlanette@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:02:29 by wlanette          #+#    #+#             */
/*   Updated: 2021/09/22 20:56:58 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
