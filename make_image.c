/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 19:19:58 by odemiany          #+#    #+#             */
/*   Updated: 2017/09/27 20:53:17 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_image(t_matrix *matrix_data, char *filename)
{
	t_mlx	mlx_data;

	create_window(filename, &mlx_data);
	print_image(&mlx_data, matrix_data);
	mlx_key_hook(mlx_data.win_ptr, my_key_func, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
}

void	create_window(char *filename, t_mlx *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, 1000, 1000, filename);
}

void	print_image(t_mlx *mlx_data, t_matrix *m_data)
{
	size_t	i;

	i = 0;
	while (i < (m_data->columns * m_data->lines) - 1)
	{
		print_line(m_data->matrix[i], m_data->matrix[i + 1], mlx_data);
		if (i < m_data->columns * (m_data->lines - 1))
			print_line(m_data->matrix[i], m_data->matrix[i + m_data->columns],
					mlx_data);
		i++;
	}
}

void	print_line(double *current, double *next, t_mlx *mlx)
{
	int		x_dif;
	int		y_dif;
	int		x_sign;
	int		y_sign;
	int		err;
	int		err2;
	int		x1;
	int		y1;
	int		x2;
	int		y2;

	x1 = (int)(current[0] * 10);
	y1 = (int)(current[1] * 10);
	x2 = (int)(next[0] * 10);
	y2 = (int)(next[1] * 10);
	x_dif = abs(x2 - x1);
	y_dif = abs(y2 - y1);
	x_sign = x1 < x2 ? 1 : -1;
	y_sign = y1 < y2 ? 1 : -1;
	err = x_dif - y_dif;
	while (x1 != x2 || y1 != y2)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x1, y1, 0x00FFFFFF);
		err2 = 2 * err;
		err = err2 > -y_dif ? -y_dif : err;
		x1 = err2 > -y_dif ? x1 + x_sign : x1;
		err = err2 < x_dif ? err + x_dif : err;
		y1 = err2 < x_dif ? y1 + y_sign : y1;
	}
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x2, y2, 0x00FFFFFF);
}

int		my_key_func(int keycode, void *param)
{
	if (keycode == 53)
	{
		mlx_destroy_window(((t_mlx *)param)->mlx_ptr,
						((t_mlx *)param)->win_ptr);
		exit(0);
	}
	return (0);
}
