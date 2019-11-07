/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 18:16:00 by mriley            #+#    #+#             */
/*   Updated: 2019/09/20 18:16:03 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_without_color(t_mlx_point *new)
{
	if (new->color == 0)
		new->color = 1;
	else if (new->color == 1)
		new->color = 0;
	new = render(new);
}

void	ft_recovery(t_mlx_point *new)
{
	new->xq = 0;
	new->yq = 0;
	new->zq = 0;
	new->wq = 1;
	new = render(new);
}

void	ft_free_coord(t_mlx_point **new)
{
	free((*new)->copy->x);
	free((*new)->copy->y);
	free((*new)->copy->z);
	free((*new)->copy);
	free((*new)->x);
	free((*new)->y);
	free((*new)->z);
	free((*new)->colors);
	mlx_destroy_image((*new)->mlx.mlx_ptr, (*new)->mlx.img.img_ptr);
	mlx_clear_window((*new)->mlx.mlx_ptr, (*new)->mlx.win);
	mlx_destroy_window((*new)->mlx.mlx_ptr, (*new)->mlx.win);
	free((*new));
	exit(0);
}

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}
