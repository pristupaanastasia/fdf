/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_four.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 18:26:31 by mriley            #+#    #+#             */
/*   Updated: 2019/09/20 18:27:47 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_moving_2(t_mlx_point *new, int keykode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (keykode == 124)
	{
		while (j < new->size)
		{
			if ((new->copy->x[j] + COEF_MOVE) >= WIN_WIDTH)
				break ;
			j++;
		}
		if (j == new->size)
			while (i < new->size)
			{
				new->copy->x[i++] += COEF_MOVE;
			}
	}
	else
		ft_moving_3(new, keykode);
}

void		ft_moving(t_mlx_point *new, int keykode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (keykode == 123)
	{
		while (j < new->size)
		{
			if ((new->copy->x[j] - COEF_MOVE) <= 0)
				break ;
			j++;
		}
		if (j == new->size)
			while (i < new->size)
			{
				new->copy->x[i++] -= COEF_MOVE;
			}
	}
	else
		ft_moving_2(new, keykode);
	new = render(new);
}

void		ft_up_down_2(t_mlx_point *new, int keykode)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (keykode == 1)
	{
		while (j < new->size)
		{
			if (new->z[j] != 0)
				if ((new->copy->y[j] + UP_DOWN) >= WIN_HEIGHT)
					break ;
			j++;
		}
		if (j == new->size)
			while (i < new->size)
			{
				if (new->z[i] != 0)
					new->copy->z[i] -= UP_DOWN;
				i++;
			}
	}
}

void		ft_up_down(t_mlx_point *new, int keykode)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (keykode == 13)
	{
		while (j < new->size)
		{
			if (new->z[j] != 0)
				if ((new->copy->y[j] - UP_DOWN) <= 0)
					break ;
			j++;
		}
		if (j == new->size)
			while (i < new->size)
			{
				if (new->z[i] != 0)
					new->copy->z[i] += UP_DOWN;
				i++;
			}
	}
	else
		ft_up_down_2(new, keykode);
	new = render(new);
}

void		ft_zoom_2(t_mlx_point *new, int keykode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (keykode == 78)
	{
		while (j < new->size)
		{
			if ((new->copy->x[1] - new->copy->x[0]) <= DELTA)
				break ;
			if (new->copy->x[j] / COEF_MINUS <= 0 ||
			new->copy->y[j] / COEF_MINUS <= 0)
				break ;
			j++;
		}
		if (j == new->size)
			while (i < new->size)
			{
				new->copy->x[i] /= COEF_MINUS;
				new->copy->y[i] /= COEF_MINUS;
				new->copy->z[i] /= COEF_MINUS;
				i++;
			}
	}
}
