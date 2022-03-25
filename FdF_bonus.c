/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:35:32 by jibot             #+#    #+#             */
/*   Updated: 2022/03/25 16:41:20 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	ft_render(t_vars *vars)
{
	int	i;
	int	fd;

	fd = open(vars->img.img_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error : wrong file name\n");
		return (0);
	}
	if (!vars->is_drawn)
	{
		i = 0;
		ft_set_black(vars);
		ft_draw_grid(fd, vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	}
	close (fd);
	return (1);
}

int	error_handle(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		ft_printf("Error : bad args input\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (error_handle(argc, argv))
		return (1);
	vars.mlx = mlx_init();
	vars.img.img_name = argv[1];
	vars.render.win_width = 1920;
	vars.render.win_height = 1080;
	vars.win = mlx_new_window(vars.mlx, vars.render.win_width, \
	vars.render.win_height, "FdF");
	vars.img.img = mlx_new_image(vars.mlx, vars.render.win_width, \
	vars.render.win_height);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bpp, \
	&vars.img.l_len, &vars.img.endian);
	vars.max_height = 10;
	vars.render.x_factor = 0.866;
	vars.render.bar_rot = 1;
	vars.render.zoom = 0;
	vars.render.height = 4;
	mlx_hook(vars.win, 2, 0, ft_key_bonus_handle, &vars);
	mlx_hook(vars.win, 4, 0, ft_buttonp_handle, &vars);
	if (!ft_render(&vars))
		return (2);
	mlx_loop_hook(vars.mlx, ft_render, &vars);
	mlx_loop(vars.mlx);
}
