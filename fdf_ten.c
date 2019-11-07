/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_ten.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 18:21:36 by mriley            #+#    #+#             */
/*   Updated: 2019/09/20 18:22:07 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mlx_point		*new_copy(t_mlx_point *new1, t_mlx_point *new,
t_matrix_rotate *rotate)
{
	ft_bzero(new, sizeof(t_mlx_point));
	if ((new->copy = (t_coords *)malloc(sizeof(*(new->copy)))) == NULL)
		exit(0);
	new->count = new1->count;
	new->size = new1->size;
	new->colors = new1->colors;
	new->color = new1->color;
	new->x = (int *)malloc(sizeof(int) * new->size);
	ft_bzero(new->x, sizeof(int) * new->size);
	new->y = (int *)malloc(sizeof(int) * new->size);
	ft_bzero(new->y, sizeof(int) * new->size);
	new->z = (int *)malloc(sizeof(int) * new->size);
	ft_bzero(new->z, sizeof(int) * new->size);
	ft_bzero(new->copy, sizeof(*(new->copy)));
	new->copy->x = (double *)malloc(sizeof(double) * new->size);
	ft_bzero(new->copy->x, sizeof(double) * new->size);
	new->copy->y = (double *)malloc(sizeof(double) * new->size);
	ft_bzero(new->copy->y, sizeof(double) * new->size);
	new->copy->z = (double *)malloc(sizeof(double) * new->size);
	ft_bzero(new->copy->z, sizeof(double) * new->size);
	new->mlx = new1->mlx;
	new1->rotate = rotate;
	return (new);
}

void			free_new(t_mlx_point *new, t_matrix_rotate *rotate)
{
	free(rotate);
	free(new->copy->x);
	free(new->copy->y);
	free(new->copy->z);
	free(new->copy);
	free(new->x);
	free(new->y);
	free(new->z);
	free(new);
}

int				check_point_rotate(t_mlx_point *new)
{
	int			i;

	i = 0;
	while (i < new->size)
	{
		if (new->copy->x[i] >= WIN_WIDTH || new->copy->x[i] <= 0
		|| new->copy->y[i] >= WIN_HEIGHT || new->copy->y[i] <= 0)
			return (0);
		i++;
	}
	return (1);
}

void			ft_draw(t_mlx_point *new1, t_matrix_rotate *rotate)
{
	int				i;
	t_mlx_point		*new;

	new = (t_mlx_point *)malloc(sizeof(t_mlx_point));
	new = new_copy(new1, new, rotate);
	i = 0;
	while (i++ < new->size)
		new = point_from_matrix(new, new1, rotate, i - 1);
	i = -1;
	new = norm_point(new1, new);
	if (check_point_rotate(new) == 1)
	{
		while (++i < new->size)
		{
			if ((i % new->count) < new->count - 1)
				ft_brez(ft_fill_coord(new, i), ft_fill_coord(new, i + 1),
				new->mlx);
			if ((i + new->count) < new->size)
				ft_brez(ft_fill_coord(new, i),
				ft_fill_coord(new, i + new->count), new->mlx);
		}
		mlx_put_image_to_window(new1->mlx.mlx_ptr, new1->mlx.win,
		new1->mlx.img.img_ptr, 0, 0);
	}
	free_new(new, rotate);
}

t_quaternion	*multiplication_qart(t_quaternion *q, t_quaternion *q2)
{
	t_quaternion	*q3;

	q3 = (t_quaternion*)malloc(sizeof(t_quaternion));
	q3->w = (q->w * q2->w - q->x * q2->x - q->y * q2->y - q->z * q2->z);
	q3->x = (q->w * q2->x + q->x * q2->w + q->y * q2->z - q->z * q2->y);
	q3->y = (q->w * q2->y - q->x * q2->z + q->y * q2->w + q->z * q2->x);
	q3->z = (q->w * q2->z + q->x * q2->y - q->y * q2->x + q->z * q2->w);
	return (q3);
}
