/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:15:39 by smanhack          #+#    #+#             */
/*   Updated: 2019/09/20 18:30:31 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx_macos/mlx.h"
# include "ft_printf_git/ft_printf.h"
# include <math.h>
# include <fcntl.h>
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1200
# define COORD_X (WIN_WIDTH / 2)
# define COORD_Y (WIN_HEIGHT / 5)
# define COEF_PLUS 2
# define COEF_MINUS 2
# define COEF_MOVE 20
# define UP_DOWN 10
# define DELTA 1

typedef struct		s_matrix_rotate
{
	double matrix[3][3];
}					t_matrix_rotate;

typedef struct		s_quaternion
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_quaternion;

typedef struct		s_img
{
	void			*img_ptr;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win;
	t_img			img;
}					t_mlx;

typedef struct		s_coord
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_coord;

typedef struct		s_coords
{
	double			*x;
	double			*y;
	double			*z;
}					t_coords;

typedef struct		s_mlx_point
{
	t_coords		*copy;
	int				*x;
	int				*y;
	int				*z;
	int				iter;
	int				color;
	int				*colors;
	double			deltax;
	double			deltay;
	double			deltaz;
	int				size;
	int				count;
	double			alfa;
	double			xq;
	double			yq;
	double			zq;
	double			wq;
	t_mlx			mlx;
	t_matrix_rotate	*rotate;
	int				but1;
	int				but2;
	int				but3;
}					t_mlx_point;

void				draw(t_mlx_point *new);
void				iso(t_mlx_point *new);
void				print_coord(t_mlx_point *new);
void				ft_cpy(t_mlx_point *new);
t_mlx_point			*render(t_mlx_point *new);
t_mlx_point			*norm_point(t_mlx_point *new, t_mlx_point *new1);
t_mlx_point			*point_from_matrix(t_mlx_point *new1, t_mlx_point *new,
					t_matrix_rotate *matrix, int i);
void				ft_brez(t_coord beg, t_coord end, t_mlx mlx);
t_coord				ft_fill_coord(t_mlx_point *new, int i);
int					key_press(int keykode, t_mlx_point *param);
void				ft_zoom(t_mlx_point *new, int keykode);
void				ft_moving(t_mlx_point *new, int keykode);
void				ft_moving_3(t_mlx_point *new, int keykode);
void				iso(t_mlx_point *new);
int					mouse_move(int x, int y, t_mlx_point *param);
void				draw(t_mlx_point *new);
void				ft_recovery(t_mlx_point *new);
void				ft_without_color(t_mlx_point *new);
void				ft_up_down(t_mlx_point *new, int keykode);
void				ft_zoom_2(t_mlx_point *new, int keykode);
int					get_color(t_coord current, t_coord start, t_coord end,
t_coord delta);
int					get_light(int start, int end, double percentage);
int					ft_write_in_coord(char *line, t_mlx_point *new, int y);
t_mlx_point			*ft_malloc_new_point(t_mlx_point *new, double count);
double				percent(int start, int end, int current);
int					ft_counter(char **line);
int					mouse_release(int button, int x, int y, t_mlx_point *param);
t_quaternion		*multiplication_qart(t_quaternion *q, t_quaternion *q2);
t_matrix_rotate		*matrix_from_quaternion(t_quaternion *q);
void				ft_draw(t_mlx_point *new1, t_matrix_rotate *rotate);
void				ft_write_in_coord_free(char **buff, int *i, int *y);
#endif
