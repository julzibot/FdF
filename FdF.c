/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:35:32 by jibot             #+#    #+#             */
/*   Updated: 2022/01/13 21:27:25 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "./libft/libft.h"
#include "get_next_line.h"

typedef struct s_render {
	int	win_width;
	int win_height;
	int margin;
	int seg_len;
	float x_factor;
	float y_factor;
	float zoom;
}	t_render;

typedef struct s_data {
  void	*img;
  char	*addr;
  int	bpp;
  int	l_len;
  int	endian;
}	t_data;

typedef struct s_vars {
	t_data		img;
	t_render	render;
	void		*mlx;
	void		*win;
	int			move_h;
	int			move_v;
	int			max_height;
	int			is_drawn;
}	t_vars;

typedef struct s_dot {
	float x_coord;
	float y_coord;
	float thick;
	int height;
	int max_height;
}	t_dot;

float	ft_min(float a, float b)
{
	if (a <= b)
		return (a);
	return (b);
}

float	ft_max(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

void	ft_mlx_pixput(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.l_len + x * (data->img.bpp / 8));
	*(unsigned int*)dst = color;
}

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

float is_grid_seg(int x, int y, t_dot *dot1, t_dot *dot2)
{
	float	coeff;
	float	abs_or;
	float	x_max;
	float	y_max;

	x_max = ft_max(dot1->x_coord, dot2->x_coord);
	y_max = ft_max(dot1->y_coord, dot2->y_coord);
	if ((x == dot1->x_coord  && dot1->x_coord == dot2->x_coord && y >= ft_min(dot1->y_coord, dot2->y_coord) && y <= y_max))
	{
		if (dot1->height != dot2->height)
			return ((y - ft_min(dot1->y_coord, dot2->y_coord)) / (y_max - ft_min(dot1->y_coord, dot2->y_coord))); 
		else
			return (0);
	}
	coeff = ((dot2->y_coord - dot1->y_coord) / (dot2->x_coord - dot1->x_coord));
	abs_or = dot1->y_coord - coeff * dot1->x_coord;
	if (x * coeff + abs_or <= y + dot1->thick && x * coeff + abs_or >= y - dot1->thick 
		&& x >= ft_min(dot1->x_coord, dot2->x_coord) && x <= x_max 
		&& y >= ft_min(dot1->y_coord, dot2->y_coord) && y <= y_max)
	{
		if (coeff > 0)
			return (1 - (x - ft_min(dot1->x_coord, dot2->x_coord)) / (x_max - ft_min(dot1->x_coord, dot2->x_coord)));
		else if (coeff < 0)
			return ((x - ft_min(dot1->x_coord, dot2->x_coord)) / (x_max - ft_min(dot1->x_coord, dot2->x_coord)));
		else
			return (0);
	}
	return (-1);
}

//sqrt(3/4) = 0.866
t_dot	*iso_coord(t_dot *dot, t_vars vars)
{
	float	x;
	float	y;
	float	y_factor;
	
	x = dot->x_coord;
	y = dot->y_coord;
	y_factor = ft_sqrt(1 - vars.render.x_factor * vars.render.x_factor);
	dot->x_coord = vars.render.x_factor * (x - y) + vars.move_h - (6 * vars.render.margin);
	dot->y_coord = y_factor * (x + y) - (4 * vars.render.x_factor * dot->height) + vars.move_v;
	return (dot);
}

t_dot	*norm_coord(t_dot *dot, t_vars vars)
{
	float	x;
	float	y;
	float	y_factor;

	y_factor = ft_sqrt(1 - vars.render.x_factor * vars.render.x_factor);
	x = dot->x_coord - vars.move_h + (6 * vars.render.margin);
	y = dot->y_coord + (4 * vars.render.x_factor * dot->height) - vars.move_v;
	dot->x_coord = 0.500 * (y / 0.500 + x / vars.render.x_factor);
	dot->y_coord = 0.500 * (y / 0.500 - x / vars.render.x_factor);
	return (dot);
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
			if (is_grid_seg(x, y, &dot1, &dot2) >= 0)
				ft_mlx_pixput(&img, x, y, color_gradient(x, y, dot1, dot2));
			y++;
		}
		x++;
	}
	return (img);
}

char	**ft_tabdup(char **data)
{
	int		i;
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
	dup[i] = NULL;
	free(data);
	return (dup);
}

int	ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
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
