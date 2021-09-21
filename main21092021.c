#include <stdio.h>
#include <stdlib.h>

// выделяем память под массивы для строк и столбцов
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

//освобождвем только строки, которые одномерные массивы
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

typedef struct s_point
{
	int x;
	int y;
}	t_point;


typedef struct	s_point_list
{
	t_point 			*point;
	struct s_point_list *next;
}						t_point_list;



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


t_point_list *push_point(t_point_list *point_list, t_point *point)
{
	t_point_list	*new_point_list;

	new_point_list = malloc(sizeof(t_point_list));

	new_point_list->point = point;
	new_point_list->next = point_list;
	return (new_point_list);
}

void print_point(t_point *point)
{
	printf("%d %d \n", point->x, point->y);
}

//пробегаемся по всему поинт листу с препятсвиями
void obs_iterate(t_point_list	*obs_list)
{
	t_point_list	*cur_obs_list;

	cur_obs_list = obs_list;
	while (1)
	{
		print_point(cur_obs_list->point);
		if (cur_obs_list->next == NULL)
			return;
		cur_obs_list = cur_obs_list->next;
	}
}

typedef struct s_rect
{
	t_point			*top_left;
	t_point			*bot_right;
	t_point_list	*form_points_list;
}					t_rect;

t_rect	*create_rect(t_point *top_left, t_point *bot_right)
{
	t_rect	*rect;

	rect = malloc(sizeof(t_rect));
	if (rect == NULL)
		return (NULL);
	rect->form_points_list = NULL;
	rect->top_left = create_point(top_left->x, top_left->y);
	rect->bot_right = create_point(bot_right->x, bot_right->y);
	return (rect);
}

void free_rect(t_rect *rect)
{
	free(rect->form_points_list);
	free(rect->top_left);
	free(rect->bot_right);
	free(rect);
}

typedef struct	s_rect_list
{
	t_rect				*rect;
	struct s_rect_list	*next;
}						t_rect_list;

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

t_rect *get_left_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_left;
	t_point	*bot_right;

	bot_right = create_point(rect->bot_right->x, obs->y - 1);

	rect_left = create_rect(rect->top_left,	bot_right);
	free(bot_right);

	return (rect_left);
}

t_rect *get_right_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_right;
	t_point	*top_left;

	top_left = create_point(rect->top_left->x, obs->y + 1);

	rect_right = create_rect(top_left,	rect->bot_right);
	free(top_left);

	return (rect_right);
}

t_rect *get_top_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_top;
	t_point	*bot_right;

	bot_right = create_point(obs->x - 1, rect->bot_right->y);

	rect_top = create_rect(rect->top_left,	bot_right);
	free(bot_right);

	return (rect_top);
}

t_rect *get_bot_rect(t_rect *rect, t_point *obs)
{
	t_rect	*rect_bot;
	t_point	*top_left;

	top_left = create_point(obs->x + 1, rect->top_left->y);

	rect_bot = create_rect(top_left, rect->bot_right);
	free(top_left);

	return (rect_bot);
}

void get_rect_cands(t_rect *rect, t_point *obs)
{
	print_point(obs);
	print_point(rect->top_left);
	print_point(rect->bot_right);



	int	delta_left;
	int	delta_right;
	int	delta_top;
	int	delta_bot;
	t_rect_list	*rect_list;

	rect_list = NULL;

	delta_left = obs->y - rect->top_left->y;
	delta_right = rect->bot_right->y - obs->y;
	delta_top = obs->x - rect->top_left->x;
	delta_bot = rect->bot_right->x - obs->x;
	printf("%d %d %d %d\n", delta_left, delta_right, delta_top, delta_bot);

	if (delta_left > 0)
	{
		rect_list = push_rect(rect_list, get_left_rect(rect, obs));
		// print_point(rect_list->rect->top_left);
		// print_point(rect_list->rect->bot_right);
		// print_point(create_point(rect->bot_right->x, obs->y - 1));
	}
	if (delta_right > 0)
	{
		rect_list = push_rect(rect_list, get_right_rect(rect, obs));
		print_point(rect_list->rect->top_left);
		print_point(rect_list->rect->bot_right);

		// print_point(create_point(rect->top_left->x, obs->y + 1));
		// print_point(rect->bot_right);
	}
	if (delta_top > 0)
	{
		rect_list = push_rect(rect_list, get_top_rect(rect, obs));
		// print_point(rect_list->rect->top_left);
		// print_point(rect_list->rect->bot_right);
		// rect_list = push_rect(rect_list,
		// 	create_rect(
		// 		rect->top_left,
		// 		create_point(obs->x - 1, rect->bot_right->y)));

		// print_point(rect->top_left);
		// print_point(create_point(obs->x - 1, rect->bot_right->y));
	}
	if (delta_bot > 0)
	{
		rect_list = push_rect(rect_list, get_bot_rect(rect, obs));
		print_point(rect_list->rect->top_left);
		print_point(rect_list->rect->bot_right);

		// rect_list = push_rect(rect_list,
		// 	create_rect(
		// 		create_point(obs->x + 1, rect->top_left->y),
		// 		rect->bot_right));

		// print_point(create_point(obs->x + 1, rect->top_left->y));
		// print_point(rect->bot_right);
	}

}



// t_point	*malloc_rect()
// {
// 	t_rect	*rect;

// 	rect = malloc(sizeof(t_rect));
// 	if (rect == NULL)
// 		return (NULL);
// 	rect->top_left = tl;
// 	rect->bot_right = br;
// 	return (rect);
// }


int main()
{
	int **field;
	int n = 9;
	int m = 11;
	// t_point *point;
	t_point_list	*obs_list;

	obs_list = NULL;

	obs_list = push_point(obs_list, create_point(5,2));
	obs_list = push_point(obs_list, create_point(2,8));
	obs_list = push_point(obs_list, create_point(2,4));

	// obs_iterate(obs_list);

	t_rect *rect;

	rect = malloc(sizeof(t_rect));
	if (rect == NULL)
		return (0);
	rect->top_left = create_point(0, 5);
	rect->bot_right = create_point(8, 10);

	get_rect_cands(rect, create_point(5, 7));

	field = malloc_2d_int_arr(n, m);
	set_zeros_2d_int_arr(field, n, m);

	field[2][4] = 1;
	field[5][7] = 1;
	// field[5][2] = 1;

	print_2d_int_arr(field, n, m);

	// printf("%llu\n", sizeof(t_point));
	// printf("%llu\n", sizeof(t_rect));

	// point = create_point(2, 4);
	// printf("%d %d\n", point->x, point->y);
	// free(point);
	// printf("%d\n", (obs_list == NULL));
	// printf("Hello\n");
	return (0);
}
