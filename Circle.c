/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:35:32 by jibot             #+#    #+#             */
/*   Updated: 2022/01/06 12:59:29 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "./libft/libft.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		endian;
}	t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	int x_center;
	int y_center;
	int radius;
	int thick;
	int move;
}	t_vars;

void	ft_mlx_pixput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	ft_is_circle(int x, int y, t_vars *circle)
{
	int sqr_sum;

	sqr_sum = ft_pwr(x - circle->x_center, 2) + ft_pwr(y - circle->y_center, 2);
	if (sqr_sum > ft_pwr(circle->radius, 2) - circle->thick \
		&& sqr_sum < ft_pwr(circle->radius, 2) + circle->thick)
		return (1);
	return (0);
}

int	ft_event_handle(int keycode, t_vars *vars)
{
	if (keycode == 0)
		vars->move = -10;
	else if (keycode == 2)
   		vars->move = 10;
	else if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (keycode);
}

t_data	ft_draw_circle(t_vars *circle, t_data img)
{
	int x;
	int y;

	circle->x_center += circle->move;
	x = 0;
	while (x < 1000)
	{
		y = 0;
		while (y < 1000)
		{
			if (ft_is_circle(x, y, circle))
				ft_mlx_pixput(&img, x, y, 0x00F0F000);
			y++;
		}
		x++;
	}
	circle->move = 0;
	return (img);
}

int	ft_render(t_vars *vars)
{
	t_data	img;

	img.img = mlx_new_image(vars->mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
	ft_draw_circle(vars, img);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	(void) argc;
	static t_vars	vars;
	t_data	img;

	vars.x_center = ft_atoi(argv[1]);
	vars.y_center = ft_atoi(argv[2]);
	vars.radius = ft_atoi(argv[3]);
	vars.thick = ft_atoi(argv[4]);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 1000, "testwin");
	img.img = mlx_new_image(vars.mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
	mlx_hook(vars.win, 2, 0, ft_event_handle, &vars);
	mlx_loop_hook(vars.mlx, ft_render, &vars);
	mlx_loop(vars.mlx);
}
