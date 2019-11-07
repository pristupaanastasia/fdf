/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_one.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:48:16 by smanhack          #+#    #+#             */
/*   Updated: 2019/09/20 18:26:18 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_quaternion	*norm_quart(t_quaternion *q)
{
	double		magn;

	magn = sqrt(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
	q->w = q->w / magn;
	q->x = q->x / magn;
	q->y = q->y / magn;
	q->z = q->z / magn;
	return (q);
}

t_quaternion	*copy_inform(t_quaternion *q2, t_mlx_point *new)
{
	new->deltax = 0.0;
	new->deltay = 0.0;
	new->deltaz = 0.0;
	q2->x = new->xq;
	q2->y = new->yq;
	q2->z = new->zq;
	q2->w = new->wq;
	return (q2);
}

t_mlx_point		*new_coord(t_mlx_point *new, t_quaternion *q3)
{
	new->xq = q3->x;
	new->yq = q3->y;
	new->zq = q3->z;
	new->wq = q3->w;
	free(q3);
	return (new);
}

t_mlx_point		*render(t_mlx_point *new)
{
	t_quaternion	*q;
	t_quaternion	*q2;
	t_matrix_rotate	*rotate;
	t_quaternion	*q3;

	q = (t_quaternion*)malloc(sizeof(t_quaternion));
	q2 = (t_quaternion*)malloc(sizeof(t_quaternion));
	new->alfa = M_PI / 180 * new->alfa;
	q->w = cos(new->alfa / 2);
	q->x = new->deltax * sin(new->alfa / 2);
	q->y = new->deltay * sin(new->alfa / 2);
	q->z = new->deltaz * sin(new->alfa / 2);
	q = norm_quart(q);
	q2 = copy_inform(q2, new);
	q2 = norm_quart(q2);
	q3 = multiplication_qart(q, q2);
	q3 = norm_quart(q3);
	rotate = matrix_from_quaternion(q3);
	ft_draw(new, rotate);
	new = new_coord(new, q3);
	free(q);
	free(q2);
	return (new);
}
