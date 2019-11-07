/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_five.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 18:16:07 by mriley            #+#    #+#             */
/*   Updated: 2019/09/20 18:28:28 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_zoom(t_mlx_point *new, int keykode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (keykode == 69)
	{
		while (j < new->size)
		{
			if (new->copy->x[j] * COEF_PLUS >= WIN_WIDTH ||
			new->copy->y[j] * COEF_PLUS >= WIN_HEIGHT)
				break ;
			j++;
		}
		if (j == new->size)
			while (i < new->size)
			{
				new->copy->x[i] *= COEF_PLUS;
				new->copy->y[i] *= COEF_PLUS;
				new->copy->z[i] *= COEF_PLUS;
				i++;
			}
	}
	ft_zoom_2(new, keykode);
	new = render(new);
}

void	key_pres_init(t_mlx_point *param)
{
	param->deltaz = 1;
	param->deltax = 0;
	param->deltay = 0;
	param->alfa = 0.5;
}

int		key_press(int keykode, t_mlx_point *param)
{
	mlx_destroy_image(param->mlx.mlx_ptr, param->mlx.img.img_ptr);
	param->mlx.img.img_ptr = mlx_new_image(param->mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT);
	param->mlx.img.data = (int *)mlx_get_data_addr(param->mlx.img.img_ptr,
	&(param->mlx.img.bpp), &(param->mlx.img.size_l), &(param->mlx.img.endian));
	if (keykode == 53)
		exit(0);
	if (keykode == 2)
	{
		key_pres_init(param);
		param = render(param);
	}
	if (keykode == 69 || keykode == 78)
		ft_zoom((t_mlx_point *)param, keykode);
	if (keykode == 13 || keykode == 1)
		ft_up_down((t_mlx_point *)param, keykode);
	if (keykode >= 123 && keykode <= 126)
		ft_moving((t_mlx_point *)param, keykode);
	if (keykode == 15)
		ft_recovery((t_mlx_point *)param);
	if (keykode == 8)
		ft_without_color((t_mlx_point *)param);
	return (0);
}

int		ft_read_16(char *str)
{
	int		i;
	int		res;

	i = 2;
	res = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 16 + (str[i++] - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			res = res * 16 + (str[i++] - 'A' + 10);
		else
			res = res * 16 + (str[i++] - 'a' + 10);
	}
	return (res);
}

int		ft_write_in_coord(char *line, t_mlx_point *new, int y)
{
	char		**buff;
	char		*color;
	int			x;
	int			i;

	buff = ft_strsplit(line, ' ');
	x = COORD_X;
	i = 0;
	while (buff[i])
	{
		new->z[new->iter + i] = ft_atoi(buff[i]);
		if ((color = ft_strchr(buff[i], ',')) != NULL)
		{
			new->colors[new->iter + i] = ft_read_16(color + 1);
			new->color = 1;
		}
		new->x[new->iter + i] = x;
		new->y[new->iter + i] = y;
		x += DELTA;
		i++;
	}
	new->iter += new->count;
	ft_write_in_coord_free(buff, &i, &y);
	return (y);
}
