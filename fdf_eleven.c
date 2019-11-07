/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_eleven.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 18:22:24 by mriley            #+#    #+#             */
/*   Updated: 2019/11/07 19:38:48 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix_rotate		*matrix_from_quaternion(t_quaternion *q)
{
	t_matrix_rotate	*rotate;

	rotate = (t_matrix_rotate*)malloc(sizeof(t_matrix_rotate));
	rotate->matrix[0][0] = 1 - 2 * q->y * q->y - 2 * q->z * q->z;
	rotate->matrix[0][1] = 2 * q->x * q->y - 2 * q->w * q->z;
	rotate->matrix[0][2] = 2 * q->x * q->z + 2 * q->w * q->y;
	rotate->matrix[1][0] = 2 * q->x * q->y + 2 * q->w * q->z;
	rotate->matrix[1][1] = 1 - 2 * q->x * q->x - 2 * q->z * q->z;
	rotate->matrix[1][2] = 2 * q->y * q->z - 2 * q->w * q->x;
	rotate->matrix[2][0] = 2 * q->x * q->z - 2 * q->w * q->y;
	rotate->matrix[2][1] = 2 * q->y * q->z + 2 * q->w * q->x;
	rotate->matrix[2][2] = 1 - 2 * q->x * q->x - 2 * q->y * q->y;
	return (rotate);
}

t_mlx_point			*point_from_matrix(t_mlx_point *new1, t_mlx_point *new,
	t_matrix_rotate *matrix, int i)
{
	double		x;
	double		y;
	double		z;

	x = new->copy->x[i] * matrix->matrix[0][0] + new->copy->y[i]
		* matrix->matrix[0][1] + new->copy->z[i] * matrix->matrix[0][2];
	y = new->copy->x[i] * matrix->matrix[1][0] + new->copy->y[i]
		* matrix->matrix[1][1] + new->copy->z[i] * matrix->matrix[1][2];
	z = new->copy->x[i] * matrix->matrix[2][0] + new->copy->y[i]
		* matrix->matrix[2][1] + new->copy->z[i] * matrix->matrix[2][2];
	new1->copy->x[i] = rint(x);
	new1->copy->y[i] = rint(y);
	new1->copy->z[i] = rint(z);
	return (new1);
}

t_mlx_point			*norm_point(t_mlx_point *new, t_mlx_point *new1)
{
	int			x;
	int			y;
	int			z;
	int			j;

	j = 0;
	x = (new->copy->x[new->count / 2 * new->count / 2]
		- new1->copy->x[new->count / 2 * new->count / 2]);
	y = (new->copy->y[new->count / 2 * new->count / 2]
		- new1->copy->y[new->count / 2 * new->count / 2]);
	z = (new->copy->z[new->count / 2 * new->count / 2]
		- new1->copy->z[new->count / 2 * new->count / 2]);
	while (j < new->size)
	{
		new1->copy->x[j] = new1->copy->x[j] + x;
		new1->copy->y[j] = new1->copy->y[j] + y;
		new1->copy->z[j] = new1->copy->z[j] + z;
		j++;
	}
	return (new1);
}

void				ft_write_in_coord_free(char **buff, int *i, int *y)
{
	*y += DELTA;
	(*i)--;
	while (*i >= 0)
	{
		free(buff[*i]);
		(*i)--;
	}
	free(buff);
}
