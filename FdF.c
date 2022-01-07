/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:35:32 by jibot             #+#    #+#             */
/*   Updated: 2022/01/07 18:46:12 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "./libft/libft.h"
#include "get_next_line.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		margin;
	int		bpp;
	int		l_len;
	int		endian;
}	t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	int win_width;
	int win_height;
	int move;
}	t_vars;

typedef struct s_dot {
	int x_coord;
	int y_coord;
	int thick;
	int height;
}	t_dot;

void	ft_mlx_pixput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	ft_event_handle(int keycode, t_vars *vars)
{
	if (keycode == 0)
		vars->move -= 2;
	else if (keycode == 2)
   		vars->move += 2;
	else if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (keycode);
}

int is_grid_seg(int x, int y, t_dot *dot1, t_dot *dot2)
{
	float coeff;
	float abs_or;

	if ((x == dot1->x_coord  && dot1->x_coord == dot2->x_coord && y >= dot1->y_coord && y <= dot2->y_coord)
		|| (y == dot1->y_coord && dot1->y_coord == dot2->y_coord && x >= dot1->x_coord && x <= dot2->x_coord))
		return (1);
	else
		coeff = ((dot2->y_coord - dot1->y_coord) / (dot2->x_coord - dot1->x_coord));
		abs_or = dot1->y_coord - coeff * dot1->x_coord;
	if (x * coeff + abs_or <= y + dot1->thick && x * coeff + abs_or >= y - dot1->thick 
		&& x >= dot1->x_coord && x <= dot2->x_coord 
		&& y >= dot1->y_coord && y <= dot2->y_coord)
		return (1);
	return (0);
}

t_data	ft_draw_line(t_data *img, t_dot *dot1, t_dot *dot2, int color)
{
	int x;
	int y;

	x = dot1->x_coord;
	while (x <= dot2->x_coord)
	{
		y = dot1->y_coord;
		while (y <= dot2->y_coord)
		{
			if (is_grid_seg(x, y, dot1, dot2))
				ft_mlx_pixput(img, x, y, color);
			y++;
		}
		x++;
	}
	return (*img);
}

char	**ft_tabdup(char **data)
{
	int i;
	char	**dup;

	i = 0;
	while (data[i])
		i++;
	dup = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (data[i])
	{
		dup[i] = data[i];
		i++;
	}
	return (dup);
}

t_data	ft_draw_grid(t_data *img, int fd)
{
	t_dot	temp_dot1;
	t_dot	temp_dot2;
	char	*buffer;
	char	**line_data;
	char	**prev_data;
	int		i;
	int		ycount;

	ycount = 0;
	buffer = get_next_line(fd);
	line_data = ft_split(buffer, ' ');
	while (line_data)
	{
		i = 0;
		prev_data = ft_tabdup(line_data);
		while (line_data[i])
		{
			temp_dot1.x_coord = 30 * (i + 1) + img->margin;
			temp_dot1.y_coord = 30 * ycount + 5 * img->margin;
			temp_dot1.height = ft_atoi(line_data[i]);
			if (line_data[i + 1])
			{
				temp_dot2.x_coord = 30 * (i + 2) + img->margin;
				temp_dot2.y_coord = 30 * ycount + 5 * img->margin;
				temp_dot2.height = ft_atoi(line_data[i + 1]);
			}
			ft_draw_line(img, &temp_dot1, &temp_dot2, 0x00FFFFFF);
			if (ycount > 0)
			{
				temp_dot2.x_coord = temp_dot1.x_coord;
				temp_dot2.y_coord = temp_dot1.y_coord - (30 * ycount);
				temp_dot2.height = ft_atoi(prev_data[i]);
				ft_draw_line(img, &temp_dot2, &temp_dot1, 0x00FFFFFF);
			}
			i++;
		}
		buffer = get_next_line(fd);
		line_data = ft_split(buffer, ' ');
		ycount++;
	}
	return (*img);
}

int	ft_render(t_vars *vars)
{
	t_data	img;
	/*t_dot	dot1;
	t_dot	dot2;

	dot1.x_coord = 100;
	dot1.y_coord = 100;
	dot2.x_coord = 800;
	dot2.y_coord = 100;
	dot1.thick = 1;*/

	int fd = open("42.fdf", O_RDONLY);
	//int fd = open("mars.fdf", O_RDONLY);
	img.img = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
	img.margin = 30;
	//ft_draw_line(&img, &dot1, &dot2, 0x00FFFFFF);
	img = ft_draw_grid(&img, fd);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_vars	vars;
	vars.mlx = mlx_init();
	vars.win_width = 1200;
	vars.win_height = 700;
	vars.win = mlx_new_window(vars.mlx, vars.win_width, vars.win_height, "FdF test");
	//mlx_hook(vars.win, 2, 0, ft_event_handle, &vars);
	//mlx_loop_hook(vars.mlx, ft_render, &vars);
	ft_render(&vars);
	mlx_loop(vars.mlx);
}
