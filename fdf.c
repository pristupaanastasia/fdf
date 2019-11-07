/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 09:34:15 by smanhack          #+#    #+#             */
/*   Updated: 2019/09/20 18:16:16 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_press(int button, int x, int y, t_mlx_point *param)
{
	(void)x;
	(void)y;
	mlx_destroy_image(param->mlx.mlx_ptr, param->mlx.img.img_ptr);
	param->mlx.img.img_ptr = mlx_new_image(param->mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT);
	param->mlx.img.data = (int *)mlx_get_data_addr(param->mlx.img.img_ptr,
	&(param->mlx.img.bpp), &(param->mlx.img.size_l), &(param->mlx.img.endian));
	param = render(param);
	if (button == 1)
		param->but1 = 1;
	if (button == 2)
		param->but2 = 1;
	if (button == 3)
		param->but3 = 1;
	return (0);
}

void	mn(t_mlx_point *new)
{
	new->but1 = 0;
	new->but2 = 0;
	new->deltax = 0;
	new->deltay = 0;
	new->deltaz = 0;
	new->xq = 0;
	new->yq = 0;
	new->zq = 0;
	new->wq = 1;
	iso(new);
	draw(new);
	mlx_hook(new->mlx.win, 2, 0, key_press, new);
	mlx_hook(new->mlx.win, 4, 0, mouse_press, new);
	mlx_hook(new->mlx.win, 5, 0, mouse_release, new);
	mlx_hook(new->mlx.win, 6, 0, mouse_move, new);
	mlx_loop(new->mlx.mlx_ptr);
}

void	mn_2(t_mlx_point *new, int arc, char **arv)
{
	char		*line;
	int			fd;
	int			y;

	y = COORD_Y;
	if ((arc == 2) && (fd = open(arv[1], O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &line) != 0)
		{
			if (new->count == 0)
			{
				new->count = ft_counter(&line);
				new = ft_malloc_new_point(new, new->count);
			}
			y = ft_write_in_coord(line, new, y);
			free(line);
			new->size += new->count;
		}
	}
	else
	{
		free(new->copy);
		free(new);
		exit(0);
	}
}

int		main(int arc, char **arv)
{
	t_mlx_point	*new;

	if ((new = (t_mlx_point*)malloc(sizeof(t_mlx_point))) == NULL)
		exit(0);
	ft_bzero(new, sizeof(t_mlx_point));
	if ((new->copy = (t_coords *)malloc(sizeof(*(new->copy)))) == NULL)
	{
		free(new);
		exit(0);
	}
	ft_bzero(new->copy, sizeof(*(new->copy)));
	new->mlx.mlx_ptr = mlx_init();
	new->mlx.win = mlx_new_window(new->mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT, "mxl 42");
	new->mlx.img.img_ptr = mlx_new_image(new->mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT);
	new->mlx.img.data = (int *)mlx_get_data_addr(new->mlx.img.img_ptr,
	&new->mlx.img.bpp, &new->mlx.img.size_l, &new->mlx.img.endian);
	mn_2(new, arc, arv);
	mn(new);
	return (0);
}
