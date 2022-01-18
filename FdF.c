/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:35:32 by jibot             #+#    #+#             */
/*   Updated: 2022/01/18 17:45:49 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	draw_x(t_vars *vars, char **line_data, int ycount)
{
	int		i;
	t_dot	temp_dot1;
	t_dot	temp_dot2;

	i = 0;
	temp_dot1.max_height = vars->max_height;
	while (line_data && line_data[i])
	{
		temp_dot1.height = ft_atoi(line_data[i]);
		temp_dot1.x_coord = vars->render.seg_len * (i + 1) + vars->render.margin;
		temp_dot1.y_coord = vars->render.seg_len * ycount + vars->render.margin;
		temp_dot1.thick = 1;
		if (line_data[i + 1])
		{
			temp_dot2.height = ft_atoi(line_data[i + 1]);
			temp_dot2.x_coord = vars->render.seg_len * (i + 2) + vars->render.margin;
			temp_dot2.y_coord = vars->render.seg_len * ycount + vars->render.margin;
		}
		else
			temp_dot2 = temp_dot1;
		ft_draw_line(*vars, *iso_coord(&temp_dot1, *vars), *iso_coord(&temp_dot2, *vars));
		i++;
	}
}

void	draw_y(t_vars *vars, char **line_data, char **prev_data, int ycount)
{
	int		i;
	t_dot	temp_dot1;
	t_dot	temp_dot2;

	i = 0;
	temp_dot1.max_height = vars->max_height;
	while (line_data && line_data[i] && ycount > 0)
	{
		vars->render.y_factor =  ft_sqrt(1 - vars->render.x_factor * vars->render.x_factor);
		temp_dot1.height = ft_atoi(line_data[i]);
		temp_dot1.x_coord = vars->render.seg_len * (i + 1) + vars->render.margin;
		temp_dot1.y_coord = vars->render.seg_len * ycount + vars->render.margin;
		temp_dot1.thick = 1;
		temp_dot2 = *iso_coord(&temp_dot1, *vars);;
		if (prev_data[i])
		{
			temp_dot2.height = ft_atoi(prev_data[i]);
			temp_dot2.x_coord += vars->render.seg_len * vars->render.x_factor * vars->render.bar_rot;
			temp_dot2.y_coord -= vars->render.seg_len * vars->render.y_factor + vars->render.height * vars->render.x_factor * (temp_dot2.height - temp_dot1.height);
		}
		ft_draw_line(*vars, temp_dot2, temp_dot1);
		i++;
	}
}


void	ft_draw_grid(int fd, t_vars *vars)
{
	char	*buffer;
	char	**line_data;
	char	**prev_data;
	int		ycount;

	ycount = 0;
	buffer = get_next_line(fd);
	line_data = ft_split(buffer, ' ');
	vars->render.margin = vars->render.win_width / 10;
	vars->render.seg_len = ((vars->render.win_width - 2 * vars->render.margin) / (2 * ft_tablen(line_data))) + vars->render.zoom;
	while (buffer)
	{
		draw_x(vars, line_data, ycount);
		draw_y(vars, line_data, prev_data, ycount);
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
	int fd = open(vars->img.img_name, O_RDONLY);

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
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.img.img_name = argv[1];
	vars.render.win_width = 1920;
	vars.render.win_height = 1080;
	vars.win = mlx_new_window(vars.mlx, vars.render.win_width, vars.render.win_height, "FdF");
	vars.img.img = mlx_new_image(vars.mlx, vars.render.win_width, vars.render.win_height);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bpp, &vars.img.l_len, &vars.img.endian);
	vars.max_height = 10;
	vars.render.x_factor = 0.866;
	vars.render.bar_rot = 1;
	//vars.render.disc_rot = 0;
	vars.render.zoom = 0;
	vars.render.height = 4;
	mlx_hook(vars.win, 2, 0, ft_key_handle, &vars);
	mlx_hook(vars.win, 4, 0, ft_buttonp_handle, &vars);
	//mlx_hook(vars.win, 6, 0, ft_button_handle, &vars);
	mlx_loop_hook(vars.mlx, ft_render, &vars);
	mlx_loop(vars.mlx);
}
