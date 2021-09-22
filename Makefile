# ************************************************************************** */
#                                                                            */
#                                                        :::      ::::::::   */
#   Makefile                                      	   :+:      :+:    :+:   */
#                                                    +:+ +:+         +:+     */
#   By: wlanette <wlanette@student.21-school.ru>   +#+  +:+       +#+        */
#                                                +#+#+#+#+#+   +#+           */
#   Created: 2021/09/20 20:29:12 by wlanette          #+#    #+#             */
#   Updated: 2021/09/20 20:29:12 by wlanette         ###   ########.fr       */
#                                                                            */
# ************************************************************************** */

SRCS		= main.c ./srcs/ft_loadfile.c ./srcs/ft_strlen.c ./srcs/validation.c ./srcs/ft_point_logic.c ./srcs/ft_rect_logic.c ./srcs/ft_rect_list_logic.c ./srcs/ft_soution.c ./srcs/ft_utils.c ./srcs/ft_check_borders.c ./srcs/ft_get_right_rect.c
OBJS		= ${SRCS:.c=.o}
INCS		= includes
NAME		= bsq
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCS}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

norm:
			norminette */*.[ch]

re:			clean all

.PHONY: all clean fclean re .c.o norm
