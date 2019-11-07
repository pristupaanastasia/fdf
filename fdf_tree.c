/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 18:16:04 by mriley            #+#    #+#             */
/*   Updated: 2019/09/20 18:29:52 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_color(t_coord current, t_coord start,
t_coord end, t_coord delta)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xFF, (end.color >> 16)
	& 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF, (end.color >> 8)
	& 0xFF, percentage);
	blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

t_coords	*point_from_matrix_coord(t_coords *new1, t_mlx_point *new,
t_matrix_rotate *matrix, int i)
{
	double	x;
	double	y;
	double	z;

	x = new->copy->x[i] * matrix->matrix[0][0] + new->copy->y[i]
	* matrix->matrix[0][1] + new->copy->z[i] * matrix->matrix[0][2];
	y = new->copy->x[i] * matrix->matrix[1][0] + new->copy->y[i]
	* matrix->matrix[1][1] + new->copy->z[i] * matrix->matrix[1][2];
	z = new->copy->x[i] * matrix->matrix[2][0] + new->copy->y[i]
	* matrix->matrix[2][1] + new->copy->z[i] * matrix->matrix[2][2];
	new1->x[i] = rint(x);
	new1->y[i] = rint(y);
	new1->z[i] = rint(z);
	return (new1);
}

t_coords	*norm_new_copy(t_coords *new, t_mlx_point *new1)
{
	double	x;
	double	y;
	double	z;
	int		j;

	j = 0;
	x = (new->x[new1->count / 2 * new1->count / 2]
	- new->x[new1->count / 2 * new1->count / 2]);
	y = (new->y[new1->count / 2 * new1->count / 2]
	- new->y[new1->count / 2 * new1->count / 2]);
	z = (new->z[new1->count / 2 * new1->count / 2]
	- new->z[new1->count / 2 * new1->count / 2]);
	while (j < new1->size)
	{
		new->x[j] = new->x[j] + x;
		new->y[j] = new->y[j] + y;
		new->z[j] = new->z[j] + z;
		j++;
	}
	return (new);
}

void		ft_moving_4(t_mlx_point *new, int keykode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (keykode == 126)
	{
		while (j < new->size)
		{
			if ((new->copy->y[j] - COEF_MOVE) <= 0)
				break ;
			j++;
		}
		if (j == new->size)
			while (i < new->size)
			{
				new->copy->y[i++] -= COEF_MOVE;
			}
	}
}

void		ft_moving_3(t_mlx_point *new, int keykode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (keykode == 125)
	{
		while (j < new->size)
		{
			if ((new->copy->y[j] + COEF_MOVE) >= WIN_HEIGHT)
				break ;
			j++;
		}
		if (j == new->size)
			while (i < new->size)
			{
				new->copy->y[i++] += COEF_MOVE;
			}
	}
	else
		ft_moving_4(new, keykode);
}
