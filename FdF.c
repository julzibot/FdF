/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:35:32 by jibot             #+#    #+#             */
/*   Updated: 2021/12/30 16:51:51 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		endian;
}	t_data;

void	ft_mlx_pixput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	int		x;
	int		y;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	x = 50;
	y = 10;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 300, 300, "testwin");
	img.img = mlx_new_image(mlx, 300, 300);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
	while (x < 150 && y < 60)
	{
		ft_mlx_pixput(&img, x, y, 0x00FF0000);
		x++;
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
