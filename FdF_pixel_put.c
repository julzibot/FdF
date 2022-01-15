/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF_pixel_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:38:31 by jibot             #+#    #+#             */
/*   Updated: 2022/01/15 15:32:11 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	ft_mlx_pixput(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.l_len + x * (data->img.bpp / 8));
	*(unsigned int*)dst = color;
}

int	color_gradient(int x, int y, t_dot dot1, t_dot dot2)
{
	float	color;
	int		max_height;

	max_height = dot1.max_height;
	if (dot1.height == dot2.height)
		color =  (int)(((float)dot1.height / (float)max_height) * 510);
	else
		color = (int)(is_grid_seg(x, y, &dot1, &dot2) * 510 * (ft_max(dot1.height, dot2.height) / max_height) + 510 * (ft_min(dot1.height, dot2.height) / max_height));
	if (color <= 255)
		return (0x00FFFFFF - color);
	else
	{
		color -= 255;
		return (0x00FFFF00 - color * ft_pwr(16, 2));
	}
	/*else
	{
		color = 765 - color;
		return (0x00FF0000 - color);
	}*/
}

t_vars	ft_draw_line(t_vars img, t_dot dot1, t_dot dot2)
{
	float	x;
	float	y;

	x = ft_min(dot1.x_coord, dot2.x_coord);
	while (x <= ft_max(dot1.x_coord, dot2.x_coord))
	{
		y = ft_min(dot1.y_coord, dot2.y_coord);
		while (y <= ft_max(dot1.y_coord, dot2.y_coord))
		{
			if (is_grid_seg(x, y, &dot1, &dot2) >= 0 && x < img.render.win_width && y < img.render.win_height)
				ft_mlx_pixput(&img, x, y, color_gradient(x, y, dot1, dot2));
			y++;
		}
		x++;
	}
	return (img);
}

void	ft_set_black(t_vars *vars)
{
	int	x;
	int	y;

	x = 0;
	while (x < vars->render.win_width)
	{
		y = 0;
		while (y < vars->render.win_height)
		{
			ft_mlx_pixput(vars, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}
