/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_nine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 18:16:17 by mriley            #+#    #+#             */
/*   Updated: 2019/09/20 18:29:26 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw(t_mlx_point *new)
{
	int	i;

	i = 0;
	while (i < new->size)
	{
		if ((i % new->count) < new->count - 1)
			ft_brez(ft_fill_coord(new, i),
			ft_fill_coord(new, i + 1), new->mlx);
		if ((i + new->count) < new->size)
			ft_brez(ft_fill_coord(new, i),
			ft_fill_coord(new, i + new->count), new->mlx);
		i++;
	}
	mlx_put_image_to_window(new->mlx.mlx_ptr,
	new->mlx.win, new->mlx.img.img_ptr, 0, 0);
}

t_mlx_point	*ft_malloc_new_point(t_mlx_point *new, double count)
{
	new->x = (int *)malloc(sizeof(int) * (count) * (count));
	ft_bzero(new->x, sizeof(int) * (count) * (count));
	new->y = (int *)malloc(sizeof(int) * (count) * (count));
	ft_bzero(new->y, sizeof(int) * (count) * (count));
	new->z = (int *)malloc(sizeof(int) * (count) * (count));
	ft_bzero(new->z, sizeof(int) * (count) * (count));
	new->copy->x = (double *)malloc(sizeof(double) * (count) * (count));
	ft_bzero(new->copy->x, sizeof(double) * (count) * (count));
	new->copy->y = (double *)malloc(sizeof(double) * (count) * (count));
	ft_bzero(new->copy->y, sizeof(double) * (count) * (count));
	new->copy->z = (double *)malloc(sizeof(double) * (count) * (count));
	ft_bzero(new->copy->z, sizeof(double) * (count) * (count));
	new->colors = (int *)malloc(sizeof(int) * (count) * (count));
	ft_memset(new->colors, 0xFFFFFF, sizeof(int) * (count) * (count));
	return (new);
}

void		iso(t_mlx_point *new)
{
	int			x;
	int			y;
	int			i;

	i = 0;
	while (i < new->size)
	{
		if ((x = new->x[i]) == 0)
			exit(0);
		if ((y = new->y[i]) == 0)
			exit(0);
		new->copy->x[i] = x;
		new->copy->y[i] = y;
		new->copy->z[i] = new->z[i];
		i++;
	}
}

int			mouse_move(int x, int y, t_mlx_point *param)
{
	mlx_destroy_image(param->mlx.mlx_ptr, param->mlx.img.img_ptr);
	param->mlx.img.img_ptr = mlx_new_image(param->mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT);
	param->mlx.img.data = (int *)mlx_get_data_addr(param->mlx.img.img_ptr,
	&(param->mlx.img.bpp), &(param->mlx.img.size_l), &(param->mlx.img.endian));
	if (param->but1 == 1)
		param->deltax = x - param->copy->x[param->size / 2] > 0 ? 5 : -5;
	if (param->but2 == 1)
		param->deltay = y - param->copy->y[param->size / 2] > 0 ? 5 : -5;
	if (param->but3 == 1)
		param->deltaz = x - param->copy->z[param->size / 2] > 0 ? 5 : -5;
	param->alfa = param->deltax * param->deltay > 0 ? 0.5 : -0.5;
	param = render(param);
	return (0);
}

int			mouse_release(int button, int x, int y, t_mlx_point *param)
{
	(void)x;
	(void)y;
	if (button == 1)
		param->but1 = 0;
	if (button == 2)
		param->but2 = 0;
	if (button == 3)
		param->but3 = 0;
	return (0);
}
