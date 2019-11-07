/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_six.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 18:16:11 by mriley            #+#    #+#             */
/*   Updated: 2019/09/20 18:29:38 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_brez_1(double delta[2], t_coord *d, t_coord *sgn, t_coord *cur)
{
	delta[1] = delta[0] * 2;
	if (delta[1] > -d->y)
	{
		delta[0] -= d->y;
		cur->x += sgn->x;
	}
	if (delta[1] < d->x)
	{
		delta[0] += d->x;
		cur->y += sgn->y;
	}
}

void	ft_brez(t_coord beg, t_coord end, t_mlx mlx)
{
	t_coord	d;
	t_coord	cur;
	t_coord	sgn;
	double	delta[2];

	cur.x = beg.x;
	cur.y = beg.y;
	d.x = fabs(end.x - beg.x);
	d.y = fabs(end.y - beg.y);
	delta[0] = d.x - d.y;
	sgn.x = beg.x < end.x ? 1 : -1;
	sgn.y = beg.y < end.y ? 1 : -1;
	mlx.img.data[(int)(end.y * WIN_WIDTH +
	end.x)] = get_color(cur, beg, end, d);
	while (cur.x != end.x || cur.y != end.y)
	{
		mlx.img.data[(int)(cur.y * WIN_WIDTH +
		cur.x)] = get_color(cur, beg, end, d);
		ft_brez_1(delta, &d, &sgn, &cur);
	}
}

int		ft_counter(char **line)
{
	char	*new_line;
	int		i;
	int		count;

	i = 0;
	count = 0;
	new_line = *line;
	while (new_line[i] != '\0')
	{
		if (new_line[i] != ' ')
		{
			while (new_line[i] != ' ' && new_line[i] != '\0')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

void	ft_fill_coord_2(t_coord *buff)
{
	if (buff->z > 0)
		buff->color = 0xF6CECE;
	else if (buff->z == 0)
		buff->color = 0xFFFFFF;
	else if (buff->z >= -80)
		buff->color = 0xCECEF6;
	else if (buff->z >= -120)
		buff->color = 0xA9A9F5;
	else if (buff->z >= -160)
		buff->color = 0x8181F7;
	else if (buff->z >= -200)
		buff->color = 0x5858FA;
	else if (buff->z >= -240)
		buff->color = 0x2E2EFE;
	else
		buff->color = 0x0000FF;
}

t_coord	ft_fill_coord(t_mlx_point *new, int i)
{
	t_coord	buff;

	buff.x = new->copy->x[i];
	buff.y = new->copy->y[i];
	buff.z = new->copy->z[i];
	if (new->color == 1)
		buff.color = new->colors[i];
	else
	{
		if (buff.z >= 240)
			buff.color = 0xFF0000;
		else if (buff.z >= 200)
			buff.color = 0xFE2E2E;
		else if (buff.z >= 160)
			buff.color = 0xFA5858;
		else if (buff.z >= 120)
			buff.color = 0xF78181;
		else if (buff.z >= 80)
			buff.color = 0xF5A9A9;
		else
			ft_fill_coord_2(&buff);
	}
	return (buff);
}
