/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:35:32 by jibot             #+#    #+#             */
/*   Updated: 2022/01/03 18:37:32 by jibot            ###   ########.fr       */
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
}	t_vars;

void	ft_mlx_pixput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	ft_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	mlx_destroy_window(vars->mlx, vars->win);
	return (keycode);
}

int	ft_move(t_data img, int keycode, t_vars *vars)
{
	int x;
	int y;

	x = 0;
	while (x < 1000)
	{
		y = 0;
		while (y < 1000)
		{
			if (*(unsigned int*)(img.addr + (y * img.l_len + x * (img.bpp / 8))) == 0x00F0F000/*[0, 240, 240, 0]*/)
			{
				if (keycode == 0)
				{
					ft_mlx_pixput(&img, x - 1, y, 0x00F0F000);
					ft_mlx_pixput(&img, x, y, 0x00000000);
				}
				else if (keycode == 2)
				{
					ft_mlx_pixput(&img, x + 1, y, 0x00F0F000);
					ft_mlx_pixput(&img, x, y, 0x00000000);
				}
			}
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (keycode);
}

int	main(void)
{
	int		x;
	int		y;
	t_vars	vars;
	t_data	img;

	x = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 1000, "testwin");
	img.img = mlx_new_image(vars.mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
	while (x < 1000)
	{
		y = 0;
		while (y < 1000)
		{
			if (ft_pwr((x - 500), 2) + ft_pwr((y - 500), 2) > ft_pwr(200, 2) - 500
				&& ft_pwr((x - 500), 2) + ft_pwr((y - 500), 2) < ft_pwr(200, 2) + 500)
				ft_mlx_pixput(&img, x, y, 0x00F0F000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//mlx_key_hook(vars.win, ft_close, &vars);
	mlx_key_hook(vars.win, ft_move, &vars);
	mlx_loop(vars.mlx);
}
