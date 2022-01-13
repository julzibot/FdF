/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:35:32 by jibot             #+#    #+#             */
/*   Updated: 2022/01/13 22:12:51 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "./libft/libft.h"
#include "get_next_line.h"
#include "FdF.h"

int	ft_key_handle(int keycode, t_vars *vars)
{
	if (keycode == 0 || keycode == 2)
		vars->move_h += (keycode - 1) * (vars->render.win_width / 300);
	else if (keycode == 13)
		vars->move_v -= (vars->render.win_height / 200);
	else if (keycode == 1)
		vars->move_v += (vars->render.win_height / 200);
	else if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	else if (keycode == 126)
		vars->max_height += 1;
	else if (keycode == 125)
		vars->max_height -= 1;
	else if (keycode == 30)
		vars->render.zoom += 1;
	else if (keycode == 33)
		vars->render.zoom -= 1;
	vars->is_drawn = 0;
	return (keycode);
}

int	ft_button_handle(int button, int x, int y, t_vars *vars)
{
	(void) x;
	(void) y;

	if (button == 4)
		vars->render.zoom -= 1;
	if (button == 5)
		vars->render.zoom += 1;
	/*vars->render.x_factor += x + y;
	vars->is_drawn = 0;*/
	return (1);
}

void	ft_draw_grid(int fd, t_vars *vars)
{
	t_dot	temp_dot1;
	t_dot	temp_dot2;
	char	*buffer;
	char	**line_data;
	char	**prev_data;
	int		i;
	int		ycount;

	ycount = 0;
	temp_dot1.max_height = vars->max_height;
	buffer = get_next_line(fd);
	line_data = ft_split(buffer, ' ');
	vars->render.margin = vars->render.win_width / 10;
	vars->render.seg_len = (vars->render.win_width - 2 * vars->render.margin) / (2 * ft_tablen(line_data));
	while (buffer)
	{
		i = 0;
		while (line_data && line_data[i])
		{
			temp_dot1.height = ft_atoi(line_data[i]);
			temp_dot1.x_coord = vars->render.seg_len * (i + 1) + vars->render.margin;
			temp_dot1.y_coord = vars->render.seg_len * ycount + vars->render.margin;
			temp_dot1.thick = 2;
			if (line_data[i + 1])
			{
				temp_dot2.height = ft_atoi(line_data[i + 1]);
				temp_dot2.x_coord = vars->render.seg_len * (i + 2) + vars->render.margin;
				temp_dot2.y_coord = vars->render.seg_len * ycount + vars->render.margin;
			}
			else
				temp_dot2 = temp_dot1;
			ft_draw_line(*vars, *iso_coord(&temp_dot1, *vars), *iso_coord(&temp_dot2, *vars));
			if (ycount > 0)
			{
				temp_dot1 = *norm_coord(&temp_dot1, *vars);
				temp_dot2 = temp_dot1;
				temp_dot2.height = ft_atoi(prev_data[i]);
				temp_dot2.y_coord -= vars->render.seg_len;
				temp_dot2.thick = 1.5;
			ft_draw_line(*vars, *iso_coord(&temp_dot2, *vars), *iso_coord(&temp_dot1, *vars));
			}
			i++;
		}
		prev_data = ft_tabdup(line_data);
		free(buffer);
		buffer = get_next_line(fd);
		line_data = ft_split(buffer, ' ');
		ycount++;
	}
	free(line_data);
	free(prev_data);
	vars->is_drawn = 1;
}

int	ft_render(t_vars *vars)
{
	int	i;
	int fd = open("42.fdf", O_RDONLY);
	//int fd = open("mars.fdf", O_RDONLY);
	//int fd = open("pyramide.fdf", O_RDONLY);
		
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

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.render.win_width = 1920;
	vars.render.win_height = 1080;
	//vars.render.margin = 50;
	//vars.render.seg_len = 40;
	vars.win = mlx_new_window(vars.mlx, vars.render.win_width, vars.render.win_height, "FdF");
	vars.img.img = mlx_new_image(vars.mlx, vars.render.win_width, vars.render.win_height);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bpp, &vars.img.l_len, &vars.img.endian);
	vars.render.zoom = 0;
	vars.max_height = 10;
	vars.render.x_factor = 0.866;
	mlx_hook(vars.win, 2, 0, ft_key_handle, &vars);
	mlx_hook(vars.win, 4, 0, ft_button_handle, &vars);
	//mlx_hook(vars.win, 6, 0, ft_button_handle, &vars);
	mlx_loop_hook(vars.mlx, ft_render, &vars);
	mlx_loop(vars.mlx);
}
