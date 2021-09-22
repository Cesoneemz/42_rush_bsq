#include <stdio.h>
#include <stdlib.h>

/*
Судя по всему достаточно пиздатый то алгоритм вышел, он работает как O(n*log(n)), где n - количество препятствий
И это позитивно, можно гонять на больших площадях, на вырожденных случаях (n=m=1 или все клетки заняты) отрабатывает правильно.

Суть такова, что алгоритм проходится по точкам препятствий (порядок не важен), а не по полю перебором.
Он целенаправлено режет поле на невложенные куски (ректы, прямоугольники),
(если вдруг отрезал вложенный кусок, то он развоплощается и не сохраняется).

Итеративно проходя каждую точку препятствий, лист ректов апдейтится целиком, заменя куски, на которых плопала текущая
точка препятстсвий на разрезанные ректы. И так пока препятствия не кончатся.

Внизу находится main, его можно погонять и проверить ситуации. нельзя только, чтоб n или m были меньше или равны нулю,
всё остальное отработает. (По идее)

Извините, но норминет ваш в рот ***л.

Комменты постарался к каждой функции написать чтоб было немного сподручнее. Если ты в vsCode, то можно прямо наводить на функции
мышкой и читать их описания.

TODO: в функции free_rect_list вылезает непонятный warning (по крайней мере у меня), может это баг дебаггера у меня, проверь
gcc с -Werror
*/

int	ft_min(int a, int b)
{
	if (a <= b)
		return a;
	else
		return b;
}

/*
Маллочим двумерный интовый массив с n строками и m столбцами.
*/
int	**malloc_2d_int_arr(int n, int m)
{
	int	**arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(int *) * n);
	if (arr == NULL)
		return (NULL);
	while (i < n)
	{
		arr[i] = malloc(sizeof(int) * m);
		if (arr[i] == NULL)
			return (NULL);
		i++;
	}
	return (arr);
}

/*
Развоплощаем двумерный интовый массив (нужно только количество строк)
*/
void	free_2d_int_arr(int **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
Делаем двумерный интовый массив нулевым
*/
void	set_zeros_2d_int_arr(int **arr, int n, int m)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < m)
		{
			arr[i][j] = 0;
			j++;
		}
		i++;
	}
}

/*
Принтим 2d array с n строками и m столбцами (осторожно, stdio.h!!!)
*/
void	print_2d_int_arr(int **arr, int n, int m)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < m)
		{
			printf("%d ", arr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

/*
Поинт. Просто поинт.
*/
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

/*
Поинт лист, великий и ужасный, используется тут вообще почти везде.
*/
typedef struct s_point_list
{
	t_point				*point;
	struct s_point_list	*next;
}						t_point_list;

/*
Создаём и маллочим поинт.
*/
t_point	*create_point(int x, int y)
{
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (point == NULL)
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

/*
Ну пуш и пуш
*/
t_point_list	*push_point(t_point_list *point_list, t_point *point)
{
	t_point_list	*new_point_list;

	new_point_list = malloc(sizeof(t_point_list));

	new_point_list->point = point;
	new_point_list->next = point_list;
	return (new_point_list);
}

/*
Осуществляем полное копирование одного поинт листа в другой с возможностью безопасного удаления старого поинт листа.
*/
t_point_list	*copy_point_list(t_point_list *old_point_list)
{
	t_point_list	*new_point_list;
	t_point_list	*temp_point_list;

	if (old_point_list == NULL)
		return (NULL);
	new_point_list = NULL;
	temp_point_list = old_point_list;
	while (temp_point_list != NULL)
	{
		new_point_list = push_point(new_point_list, temp_point_list->point);
		temp_point_list = temp_point_list->next;
	}
	return (new_point_list);


	// new_point_list
	// copy_point_list(new_point_list->next, old_point_list->next);
	// new_point_list->next
	// new_point_list

}

/*
Рекурсивно развоплощаем поинт лист, однако сами поинты и ссылки на них не трогаем.
*/
void free_point_list(t_point_list *point_list)
{
	if (point_list == NULL)
		return ;
	if (point_list->next == NULL)
	{
		free(point_list);
		return ;
	}
	else
	{
		free_point_list(point_list->next);
		free(point_list);
		return ;
	}
}

/*
Ну так, дебага ради
*/
// void	print_point(t_point *point)
// {
// 	printf("%d %d \n", point->x, point->y);
// }

/*
Ну так, дебага ради
*/
// void	print_tpoint_list(t_point_list	*obs_list)
// {
// 	t_point_list	*cur_obs_list;

// 	if (obs_list == NULL)
// 	{
// 		printf("NULL\n");
// 		return ;
// 	}

// 	cur_obs_list = obs_list;
// 	while (1)
// 	{
// 		print_point(cur_obs_list->point);
// 		if (cur_obs_list->next == NULL)
// 			return ;
// 		cur_obs_list = cur_obs_list->next;
// 	}
// }

/*
Рект. Прямоугольник. В итоге нужно найти самый большой прямоугольник на площади.
Каждый прямоугольник имеет границы, вдоль границ располагаются либо препятствия,
породившие прямоугольник, либо край карты. Край карты - поинт лист NULL.
Если не NULL - значит граница порождена препятствием или несколькими препятствиями.
*/
typedef struct s_rect
{
	t_point			*top_left;
	t_point			*bot_right;
	// t_point_list	*form_points_list;
	t_point_list	*point_list_left;
	t_point_list	*point_list_right;
	t_point_list	*point_list_top;
	t_point_list	*point_list_bot;
}					t_rect;

/*
Создаём чистый рект. NULL на границах означает границу поля в целом,
что позволяет избегать дополнительных проверок и сложностей.
*/
t_rect	*create_rect(t_point *top_left, t_point *bot_right)
{
	t_rect	*rect;

	rect = malloc(sizeof(t_rect));
	if (rect == NULL)
		return (NULL);
	rect->point_list_left = NULL;
	rect->point_list_right = NULL;
	rect->point_list_top = NULL;
	rect->point_list_bot = NULL;
	rect->top_left = create_point(top_left->x, top_left->y);
	rect->bot_right = create_point(bot_right->x, bot_right->y);
	return (rect);
}

/*
В отличие от create_rect, где рект создаётся "с нуля", здесь считаем, что все
поинт листы передаются следующему ректу.
Также происходит полное копирование поинт листов по всем направлениям так как
предполагается, что порождающий base_rect может быть уничтожен в любой момент,
в т ч сразу создания наследника.
*/
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
/*
Подчищаем рект, чистим поинт листы по границам, однако не затираем ни ссылки, ни значения непосредственно поинтов в поинт листах.
Значения поинтов в процессе всего алгоритма - иммутабельны, их затирать нельзя.
*/
void free_rect(t_rect *rect)
{
	free_point_list(rect->point_list_left);
	free_point_list(rect->point_list_right);
	free_point_list(rect->point_list_top);
	free_point_list(rect->point_list_bot);
	free(rect->top_left);
	free(rect->bot_right);
	free(rect);
}

/*
Рект лист, который содержит столь необходимые ректы.
*/
typedef struct	s_rect_list
{
	t_rect				*rect;
	struct s_rect_list	*next;
}						t_rect_list;

/*
Ну пушим и пушим.
*/
t_rect_list *push_rect(t_rect_list *rect_list, t_rect *rect)
{
	t_rect_list	*new_rect_list;

	if (rect == NULL)
		return (rect_list);
	new_rect_list = malloc(sizeof(t_rect_list));
	new_rect_list->rect = rect;
	new_rect_list->next = rect_list;
	return (new_rect_list);
}

/*
Освобождаем рект лист вместе без ректов.
Функция используется при перекидывании одних и тех же ректов по разным рект листам туды сюды.
Ссылки на полезные ректы не теряются, бесполезные ректы - затираются в конце функции get_rect_cands()
*/
void	free_rect_list(t_rect_list *rect_list)
{
	if (rect_list == NULL)
		return ;
	if (rect_list->next == NULL)
	{
		free(rect_list);
		return ;
	}
	else
	{
		free_point_list(rect_list->next);
		free(rect_list);
		return ;
	}
}

/*
Полностью освобождаем рект лист вместе с входящими в него ректами.
Нужно только один раз - после заполнения двумерного массива, т е после окончания всего.
*/
void	free_full_rect_list(t_rect_list *rect_list)
{
	t_rect_list	*temp_rect_list;

	temp_rect_list = rect_list;
	while (temp_rect_list != NULL)
	{
		free_rect(temp_rect_list->rect);
		temp_rect_list = temp_rect_list ->next;
	}
	free_rect_list(rect_list);

}

/*
Проверяем корректность левых ограничивающих точек.
Убираем те точки что не попадают в диапазон входного ректа.
Если ограничивающих точек в диапазоне ректа слева нет, значит рект скипаем.
*/
int	check_left_border_rules(t_rect *rect)
{
	t_point_list *temp_point_list;
	t_point_list *last_ok_point_list;
	t_point_list *to_remove_point_list;

	if (rect->point_list_left == NULL)
		return (1);
	last_ok_point_list = NULL;
	to_remove_point_list = NULL;

	temp_point_list = rect->point_list_left;
	while (temp_point_list != NULL)
	{
		if (temp_point_list->point->x >= rect->top_left->x &&
			temp_point_list->point->x <= rect->bot_right->x)
			last_ok_point_list = push_point(last_ok_point_list,
				temp_point_list->point);
		else
			to_remove_point_list = push_point(to_remove_point_list,
				temp_point_list->point);

		temp_point_list = temp_point_list->next;
	}

	if (last_ok_point_list == NULL)
	{
		// printf("Bad left border\n");
		return (0);
	}

	rect ->point_list_left = last_ok_point_list;
	free_point_list(to_remove_point_list);

	return (1);
}

/*
Проверяем корректность правых ограничивающих точек.
Убираем те точки что не попадают в диапазон входного ректа.
Если ограничивающих точек в диапазоне ректа справа нет, значит рект скипаем.
*/
int	check_right_border_rules(t_rect *rect)
{
	t_point_list *temp_point_list;
	t_point_list *last_ok_point_list;
	t_point_list *to_remove_point_list;

	if (rect->point_list_right == NULL)
		return (1);
	last_ok_point_list = NULL;
	to_remove_point_list = NULL;

	temp_point_list = rect->point_list_right;
	while (temp_point_list != NULL)
	{
		if (temp_point_list->point->x >= rect->top_left->x &&
			temp_point_list->point->x <= rect->bot_right->x)
			last_ok_point_list = push_point(last_ok_point_list,
				temp_point_list->point);
		else
			to_remove_point_list = push_point(to_remove_point_list,
				temp_point_list->point);

		temp_point_list = temp_point_list->next;
	}

	if (last_ok_point_list == NULL)
	{
		// printf("Bad right border\n");
		return (0);
	}

	rect ->point_list_right = last_ok_point_list;
	free_point_list(to_remove_point_list);

	return (1);
}

/*
Проверяем корректность верхних ограничивающих точек.
Убираем те точки что не попадают в диапазон входного ректа.
Если ограничивающих точек в диапазоне ректа сверху нет, значит рект скипаем.
*/
int	check_top_border_rules(t_rect *rect)
{
	t_point_list *temp_point_list;
	t_point_list *last_ok_point_list;
	t_point_list *to_remove_point_list;

	if (rect->point_list_top == NULL)
		return (1);
	last_ok_point_list = NULL;
	to_remove_point_list = NULL;

	temp_point_list = rect->point_list_top;
	while (temp_point_list != NULL)
	{
		if (temp_point_list->point->y >= rect->top_left->y &&
			temp_point_list->point->y <= rect->bot_right->y)
			last_ok_point_list = push_point(last_ok_point_list,
				temp_point_list->point);
		else
			to_remove_point_list = push_point(to_remove_point_list,
				temp_point_list->point);

		temp_point_list = temp_point_list->next;
	}

	if (last_ok_point_list == NULL)
	{
		// printf("Bad top border\n");
		return (0);
	}

	rect ->point_list_top = last_ok_point_list;
	free_point_list(to_remove_point_list);

	return (1);
}
/*
Проверяем корректность нижних ограничивающих точек.
Убираем те точки что не попадают в диапазон входного ректа.
Если ограничивающих точек в диапазоне ректа снизу нет, значит рект скипаем.
*/
int	check_bot_border_rules(t_rect *rect)
{
	t_point_list *temp_point_list;
	t_point_list *last_ok_point_list;
	t_point_list *to_remove_point_list;

	if (rect->point_list_bot == NULL)
		return (1);
	last_ok_point_list = NULL;
	to_remove_point_list = NULL;

	temp_point_list = rect->point_list_bot;
	while (temp_point_list != NULL)
	{
		if (temp_point_list->point->y >= rect->top_left->y &&
			temp_point_list->point->y <= rect->bot_right->y)
			last_ok_point_list = push_point(last_ok_point_list,
				temp_point_list->point);
		else
			to_remove_point_list = push_point(to_remove_point_list,
				temp_point_list->point);

		temp_point_list = temp_point_list->next;
	}

	if (last_ok_point_list == NULL)
	{
		// printf("Bad bot border\n");
		return (0);
	}

	rect ->point_list_bot = last_ok_point_list;
	free_point_list(to_remove_point_list);

	return (1);
}
/*
Пытаемся получить левый рект при его разбивке.
*/
t_rect	*get_left_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_left;
	t_point	*bot_right;

	bot_right = create_point(rect->bot_right->x, obs->y - 1);

	rect_left = inherit_rect(rect->top_left, bot_right, rect);
	free(bot_right);


	rect_left->point_list_right = NULL;
	rect_left->point_list_right = push_point(rect_left->point_list_right, obs);

	// return (rect_left);
	if (check_left_border_rules(rect_left) &&
		check_right_border_rules(rect_left) &&
		check_top_border_rules(rect_left) &&
		check_bot_border_rules(rect_left))
		return (rect_left);
	else
		return (NULL);
}
/*
Пытаемся получить правый рект при его разбивке.
*/
t_rect	*get_right_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_right;
	t_point	*top_left;

	top_left = create_point(rect->top_left->x, obs->y + 1);

	rect_right = inherit_rect(top_left,	rect->bot_right, rect);
	free(top_left);

	rect_right->point_list_left = NULL;
	rect_right->point_list_left = push_point(rect_right->point_list_left, obs);

	if (check_left_border_rules(rect_right) &&
		check_right_border_rules(rect_right) &&
		check_top_border_rules(rect_right) &&
		check_bot_border_rules(rect_right))
		return (rect_right);
	else
		return (NULL);
}
/*
Пытаемся получить верхний рект при его разбивке.
*/
t_rect	*get_top_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_top;
	t_point	*bot_right;

	bot_right = create_point(obs->x - 1, rect->bot_right->y);

	rect_top = inherit_rect(rect->top_left,	bot_right, rect);
	free(bot_right);

	rect_top->point_list_bot = NULL;
	rect_top->point_list_bot = push_point(rect_top->point_list_bot, obs);

	if (check_left_border_rules(rect_top) &&
		check_right_border_rules(rect_top) &&
		check_top_border_rules(rect_top) &&
		check_bot_border_rules(rect_top))
		return (rect_top);
	else
		return (NULL);

	// return (rect_top);
}
/*
Пытаемся получить нижний рект при его разбивке.
*/
t_rect	*get_bot_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_bot;
	t_point	*top_left;

	top_left = create_point(obs->x + 1, rect->top_left->y);

	rect_bot = inherit_rect(top_left, rect->bot_right, rect);
	free(top_left);

	rect_bot->point_list_top = NULL;
	rect_bot->point_list_top = push_point(rect_bot->point_list_top, obs);

	if (check_left_border_rules(rect_bot) &&
		check_right_border_rules(rect_bot) &&
		check_top_border_rules(rect_bot) &&
		check_bot_border_rules(rect_bot))
		return (rect_bot);
	else
		return (NULL);
	// return (rect_bot);
}


/*
Ебать мякотка. Я оставил принтфы для истории.

Функция берёт рект, берёт точку и пытается
разделить рект на 4 ректа: слева, справа, сверху, снизу.

Полученные ректы списком пушатся к new_rect_list.

Какие-то ректы по разным причинам могут не получиться, они пропускаются.
Если вообще никакие ректы не получилось распилить, возвращается NULL.

Если точка вне ректа, то пушим к new_rect_list входной рект.
*/
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
		// printf("Out of range \n");
		new_rect_list = push_rect(new_rect_list, rect);
		return (new_rect_list);
	}
	// printf("%d %d %d %d\n", delta_left, delta_right, delta_top, delta_bot);
	// print_point(rect->form_points_list->point);
	if (delta_left > 0)
	{
		new_rect_list = push_rect(new_rect_list, get_left_rect(rect, obs));
		// printf("Left\n");
		// print_point(new_rect_list->rect->top_left);
		// print_point(new_rect_list->rect->bot_right);
		// printf("Left: Left border\n");
		// print_tpoint_list(rect_list->rect->point_list_left);
		// printf("Left: Right border\n");
		// print_tpoint_list(rect_list->rect->point_list_right);
		// printf("Left: Top border\n");
		// print_tpoint_list(rect_list->rect->point_list_top);
		// printf("Left: Bottom border\n");
		// print_tpoint_list(rect_list->rect->point_list_bot);
		// print_point(create_point(rect->bot_right->x, obs->y - 1));
	}
	if (delta_right > 0)
	{
		new_rect_list = push_rect(new_rect_list, get_right_rect(rect, obs));
		// printf("Right\n");
		// print_point(new_rect_list->rect->top_left);
		// print_point(new_rect_list->rect->bot_right);
		// printf("Right: Left border\n");
		// print_tpoint_list(rect_list->rect->point_list_left);
		// printf("Right: Right border\n");
		// print_tpoint_list(rect_list->rect->point_list_right);
		// printf("Right: Top border\n");
		// print_tpoint_list(rect_list->rect->point_list_top);
		// printf("Right: Bottom border\n");
		// print_tpoint_list(rect_list->rect->point_list_bot);

		// print_point(create_point(rect->top_left->x, obs->y + 1));
		// print_point(rect->bot_right);
	}
	if (delta_top > 0)
	{
		new_rect_list = push_rect(new_rect_list, get_top_rect(rect, obs));
		// printf("Top\n");
		// print_point(new_rect_list->rect->top_left);
		// print_point(new_rect_list->rect->bot_right);
		// printf("Top: Left border\n");
		// print_tpoint_list(rect_list->rect->point_list_left);
		// printf("Top: Right border\n");
		// print_tpoint_list(rect_list->rect->point_list_right);
		// printf("Top: Top border\n");
		// print_tpoint_list(rect_list->rect->point_list_top);
		// printf("Top: Bottom border\n");
		// print_tpoint_list(rect_list->rect->point_list_bot);
		// rect_list = push_rect(rect_list,
		// 	create_rect(
		// 		rect->top_left,
		// 		create_point(obs->x - 1, rect->bot_right->y)));

		// print_point(rect->top_left);
		// print_point(create_point(obs->x - 1, rect->bot_right->y));
	}
	if (delta_bot > 0)
	{
		new_rect_list = push_rect(new_rect_list, get_bot_rect(rect, obs));
		// printf("Bottom\n");
		// print_point(new_rect_list->rect->top_left);
		// print_point(new_rect_list->rect->bot_right);
		// printf("Bottom: Left border\n");
		// print_tpoint_list(rect_list->rect->point_list_left);
		// printf("Bottom: Right border\n");
		// print_tpoint_list(rect_list->rect->point_list_right);
		// printf("Bottom: Top border\n");
		// print_tpoint_list(rect_list->rect->point_list_top);
		// printf("Bottom: Bottom border\n");
		// print_tpoint_list(rect_list->rect->point_list_bot);

		// rect_list = push_rect(rect_list,
		// 	create_rect(
		// 		create_point(obs->x + 1, rect->top_left->y),
		// 		rect->bot_right));

		// print_point(create_point(obs->x + 1, rect->top_left->y));
		// print_point(rect->bot_right);
	}
	free_rect(rect);
	return (new_rect_list);
}

/*
Получаем список всех доступных невложенных (!) прямоугольников с учётом
препятствий в obs_list и соотв. размерами поля
*/
t_rect_list	*get_rects_list(t_point_list *obs_list, int n, int m)
{
	t_rect_list		*full_rect_list;
	t_rect_list		*new_rect_list;
	t_rect_list		*temp_rect_list;
	t_point_list	*temp_obs_list;

	full_rect_list = NULL;
	new_rect_list = NULL;
	full_rect_list = push_rect(full_rect_list,
		create_rect(create_point(0, 0), create_point(n - 1, m - 1)));
	temp_obs_list = obs_list;
	while (temp_obs_list != NULL)
	{
		temp_rect_list = full_rect_list;
		while (temp_rect_list != NULL)
		{
			new_rect_list = get_rect_cands(temp_rect_list->rect,
				temp_obs_list->point, new_rect_list);
			temp_rect_list = temp_rect_list->next;
		}
		free_rect_list(full_rect_list);
		full_rect_list = new_rect_list; // оп, prekol
		new_rect_list = NULL;
		temp_obs_list = temp_obs_list->next;
	}
	return (full_rect_list); // если возвращает NULL, значит не может найти хотя бы одну точку
}

/*
Получаем максимальный прямоугольник из имеющегося листа ректов. Просто тупа перебор по листу.
*/
t_rect *get_max_rect(t_rect_list *rect_list)
{
	t_rect			*max_rect;
	t_rect_list		*temp_rect_list;
	int				max_size;
	int				cur_size;

	max_rect = rect_list->rect;
	max_size = ft_min(rect_list->rect->bot_right->x -
			rect_list->rect->top_left->x,
		rect_list->rect->bot_right->y -
			rect_list->rect->top_left->y);
	temp_rect_list = rect_list;
	while (temp_rect_list != NULL)
	{
		cur_size = ft_min(temp_rect_list->rect->bot_right->x -
				temp_rect_list->rect->top_left->x,
			temp_rect_list->rect->bot_right->y -
				temp_rect_list->rect->top_left->y);
		if (max_size < cur_size)
		{
			max_rect = temp_rect_list->rect;
			max_size = cur_size;
		}
		temp_rect_list = temp_rect_list -> next;
	}
	return (max_rect);
}

// Заполням максимальный квадрат в прямоугольнике rect значениями value
void fill_square_2d_int_arr(int **arr, t_rect *rect, int value)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = ft_min(rect->bot_right->x - rect->top_left->x,
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
}



int **get_filled_field(t_point_list *obs_list, int n, int m)
{
	int 			**field;
	t_point_list	*temp_obs_list;
	t_rect_list		*rect_list;
	t_rect			*max_rect;

	field = malloc_2d_int_arr(n, m);
	// Заполним нулями всё
	set_zeros_2d_int_arr(field, n, m);
	// Заполним единицами обстаклы
	temp_obs_list = obs_list;
	while (temp_obs_list != NULL)
	{
		field[temp_obs_list->point->x][temp_obs_list->point->y] = 1;
		temp_obs_list = temp_obs_list->next;
	}
	// Найдем лист из всех доступных невложенных прямоугольников
	rect_list = get_rects_list(obs_list, n, m);
	if (rect_list == NULL) // NULL - значит нет места вообще
		return (NULL);

	// Найдём максимальное поле для квадрата
	max_rect = get_max_rect(rect_list);

	// Заполним максимальный квадрат двойками
	fill_square_2d_int_arr(field, max_rect, 2);

	// Почистим мусор полностью
	free_full_rect_list(rect_list);
	return (field);
}

int	main()
{
	int n = 9;
	int m = 11;
	int **field;
	t_point_list	*obs_list;

	// вот так надо задавать список препятствий
	obs_list = NULL;
	// obs_list = push_point(obs_list, create_point(3,7));
	obs_list = push_point(obs_list, create_point(5,4));
	obs_list = push_point(obs_list, create_point(2,4));
	obs_list = push_point(obs_list, create_point(5,7));

	// получим заполненное поле - двумерный интовый массив
	field = get_filled_field(obs_list, n, m);
	if (field == NULL)
		printf("map error\n");	// NULL - значит не получилось
	else
		print_2d_int_arr(field, n, m);

	return (0);

	// int **field;
	// int n = 9;
	// int m = 11;
	// // t_point *point;
	// t_point_list	*obs_list;
	// t_point_list	*list_left;
	// t_point_list	*list_right;
	// t_point_list	*list_top;
	// t_point_list	*list_bot;
	// t_rect_list		*full_rect_list;
	// t_rect_list		*temp_rect_list;
	// t_rect_list		*test_rect_list;
	// // t_point_list	*test;

	// obs_list = NULL;
	// list_left = NULL;
	// list_right = NULL;
	// list_top = NULL;
	// list_bot = NULL;


	// obs_list = push_point(obs_list, create_point(2,4));
	// obs_list = push_point(obs_list, create_point(8,4));
	// obs_list = push_point(obs_list, create_point(0,0));
	// obs_list = push_point(obs_list, create_point(1,1));
	// obs_list = push_point(obs_list, create_point(2,2));
	// obs_list = push_point(obs_list, create_point(3,3));
	// obs_list = push_point(obs_list, create_point(5,4));
	// obs_list = push_point(obs_list, create_point(2,4));
	// obs_list = push_point(obs_list, create_point(5,7));

	// get_rects_list(obs_list, n, m);

	// obs_list = push_point(obs_list, create_point(0,0));
	// obs_list = push_point(obs_list, create_point(0,1));
	// obs_list = push_point(obs_list, create_point(1,0));
	// obs_list = push_point(obs_list, create_point(1,1));
	// get_rects_list(obs_list, 1, 1);
	// full_rect_list = NULL;
	// test_rect_list = NULL;
	// full_rect_list = push_rect(full_rect_list,
	// 	create_rect(create_point(0, 0), create_point(n - 1, m - 1)));

	// temp_rect_list = get_rect_cands()
	// temp_rect_list = full_rect_list;
	// while (temp_rect_list != NULL)
	// {
	// 	test_rect_list = get_rect_cands(temp_rect_list->rect, obs_list->point);
	// 	temp_rect_list = temp_rect_list->next;
	// }

	// temp_rect_list = test_rect_list;
	// while (temp_rect_list != NULL)
	// {
	// 	// printf("New Iter\n");
	// 	// print_point(temp_rect_list->rect->top_left);
	// 	// print_point(temp_rect_list->rect->bot_right);
	// 	get_rect_cands(temp_rect_list->rect, obs_list->next->point);
	// 	temp_rect_list = temp_rect_list->next;
	// }




	// obs_iterate(obs_list);

	// t_rect *rect;

	// rect = malloc(sizeof(t_rect));
	// if (rect == NULL)
	// 	return (0);
	// rect->top_left = create_point(2, 4);
	// rect->bot_right = create_point(8, 9);

	// list_left = push_point(list_left, create_point(0, 3));
	// list_left = push_point(list_left, create_point(3, 3));
	// list_left = push_point(list_left, create_point(7, 3));
	// list_left = push_point(list_left, create_point(10, 3));

	// list_right = push_point(list_right, create_point(0, 10));
	// list_right = push_point(list_right, create_point(2, 10));
	// list_right = push_point(list_right, create_point(4, 10));
	// list_right = push_point(list_right, create_point(10, 10));
	// list_right = push_point(list_right, create_point(6, 10));

	// list_top = push_point(list_top, create_point(1, 1));
	// list_top = push_point(list_top, create_point(1, 8));
	// list_top = push_point(list_top, create_point(1, 4));
	// list_top = push_point(list_top, create_point(1, 11));

	// list_bot = push_point(list_bot, create_point(9, 1));
	// list_bot = push_point(list_bot, create_point(9, 6));
	// list_bot = push_point(list_bot, create_point(9, 5));
	// list_bot = push_point(list_bot, create_point(9, 9));
	// list_bot = push_point(list_bot, create_point(9, 11));
	// // list_left = push_point(list_left, obs_list->point);
	// // list_left = push_point(list_left, obs_list->next->point);
	// // list_left = push_point(list_left, obs_list->next->next->point);
	// // list_left = push_point(list_left, obs_list->next->next->next->point);

	// // printf("Obs list check\n");
	// // print_tpoint_list(obs_list);



	// rect->point_list_left = list_left;
	// rect->point_list_right = list_right;
	// rect->point_list_top = list_top;
	// rect->point_list_bot = list_bot;
	// // rect->form_points_list = obs_list;
	// get_rect_cands(rect, create_point(5, 6));
	// // get_rect_cands(rect, create_point(20, 7));


	// free_rect(rect);
	// // printf("Obs list check 2\n");
	// // print_tpoint_list(obs_list);


	// field = malloc_2d_int_arr(n, m);
	// set_zeros_2d_int_arr(field, n, m);

	// field[2][4] = 1;
	// field[5][7] = 1;
	// field[5][4] = 1;
	// field[0][0] = 1;
	// field[1][1] = 1;
	// field[2][2] = 1;
	// field[3][3] = 1;
	// // field[7][4] = 1;
	// // field[5][2] = 1;

	// print_2d_int_arr(field, n, m);

	// printf("%llu\n", sizeof(t_point));
	// printf("%llu\n", sizeof(t_rect));

	// point = create_point(2, 4);
	// printf("%d %d\n", point->x, point->y);
	// free(point);
	// printf("%d\n", (obs_list == NULL));
	// printf("Hello\n");

}
