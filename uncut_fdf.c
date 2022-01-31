/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:35:32 by jibot             #+#    #+#             */
/*   Updated: 2022/01/12 16:45:58 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "./libft/libft.h"
#include "get_next_line.h"

typedef struct s_vars {
	void	*img;
	//void	*t_img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		win_width;
	int		win_height;
	int		move_h;
	int		move_v;
	int		margin;
	int		bpp;
	int		l_len;
	int		endian;
	int		is_drawn;
}	t_vars;

/*typedef struct s_vars {
  void	*mlx;
  void	*win;
  int		win_width;
  int		win_height;
  int		move_h;
  int		move_v;
  }	t_vars;*/

typedef struct s_dot {
	float x_coord;
	float y_coord;
	float thick;
	int height;
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

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	ft_event_handle(int keycode, t_vars *vars)
{
	if (keycode == 0 || keycode == 2)
		vars->move_h += (keycode - 1) * 4;
	else if (keycode == 13)
		vars->move_v -= 4;
	else if (keycode == 1)
		vars->move_v += 4;
	else if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (keycode);
}

int is_grid_seg(int x, int y, t_dot *dot1, t_dot *dot2)
{
	float	coeff;
	float	abs_or;
	float	x_max;
	float	y_max;

	x_max = ft_max(dot1->x_coord, dot2->x_coord);
	y_max = ft_max(dot1->y_coord, dot2->y_coord);
	if ((x == dot1->x_coord  && dot1->x_coord == dot2->x_coord && y >= ft_min(dot1->y_coord, dot2->y_coord) && y <= y_max)
			|| (y == dot1->y_coord && dot1->y_coord == dot2->y_coord && x >= ft_min(dot1->x_coord, dot2->x_coord) && x <= x_max))
		return (1);
	coeff = ((dot2->y_coord - dot1->y_coord) / (dot2->x_coord - dot1->x_coord));
	abs_or = dot1->y_coord - coeff * dot1->x_coord;
	if (x * coeff + abs_or <= y + dot1->thick && x * coeff + abs_or >= y - dot1->thick 
			&& x >= ft_min(dot1->x_coord, dot2->x_coord) && x <= x_max 
			&& y >= ft_min(dot1->y_coord, dot2->y_coord) && y <= y_max)
		return (1);
	return (0);
}

//sqrt(3/4) = 0.866
t_dot	*iso_coord(t_dot *dot, t_vars vars)
{
	float	x;
	float	y;

	x = dot->x_coord;
	y = dot->y_coord;
	dot->x_coord = 0.866 * (x - y) + vars.move_h;
	dot->y_coord = 0.500 * (x + y) - (4 * 0.866 * dot->height) + vars.move_v;
	return (dot);
}

t_dot	*norm_coord(t_dot *dot, t_vars vars)
{
	float	x;
	float	y;

	x = dot->x_coord - vars.move_h;
	y = dot->y_coord + (4 * 0.866 * dot->height) - vars.move_v;
	dot->x_coord = 0.500 * (y / 0.500 + x / 0.866);
	dot->y_coord = 0.500 * (y / 0.500 - x / 0.866);
	return (dot);
}

t_vars	ft_draw_line(t_vars img, t_dot dot1, t_dot dot2, int color)
{
	float x;
	float y;

	x = ft_min(dot1.x_coord, dot2.x_coord);
	while (x <= ft_max(dot1.x_coord, dot2.x_coord))
	{
		y = ft_min(dot1.y_coord, dot2.y_coord);
		while (y <= ft_max(dot1.y_coord, dot2.y_coord))
		{
			if (is_grid_seg(x, y, &dot1, &dot2))
				ft_mlx_pixput(&img, x, y, color);
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

t_vars	ft_draw_grid(int fd, t_vars vars)
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
		while (line_data && line_data[i])
		{
			temp_dot1.height = ft_atoi(line_data[i]);
			temp_dot1.x_coord = 25 * (i + 1) + 1 * vars.margin;
			temp_dot1.y_coord = 25 * ycount + 10 * vars.margin;
			temp_dot1.thick = 1;
			if (line_data[i + 1])
			{
				temp_dot2.height = ft_atoi(line_data[i + 1]);
				temp_dot2.x_coord = 25 * (i + 2) + 1 * vars.margin;
				temp_dot2.y_coord = 25 * ycount + 10 *vars.margin;
			}
			else
				temp_dot2 = temp_dot1;
			ft_draw_line(vars, *iso_coord(&temp_dot1, vars), *iso_coord(&temp_dot2, vars),  0x00FFFFFF);
			if (ycount > 0)
			{
				temp_dot1 = *norm_coord(&temp_dot1, vars);
				temp_dot2 = temp_dot1;
				temp_dot2.height = ft_atoi(prev_data[i]);
				temp_dot2.y_coord -= 25;
				temp_dot2.thick = 0.5;
				ft_draw_line(vars, *iso_coord(&temp_dot1, vars), *iso_coord(&temp_dot2, vars), 0x00FFFFFF);
			}
			i++;
		}
		prev_data = ft_tabdup(line_data);
		tamere = 1;
		buffer = get_next_line(fd);
		line_data = ft_split(buffer, ' ');
		ycount++;
	}
	free(buffer);
	free(line_data);
	free(prev_data);
	return (vars);
}

void	ft_set_black(t_vars *vars)
{
	int	x;
	int	y;

	x = 0;
	while (x < vars->win_width)
	{
		y = 0;
		while (y < vars->win_height)
		{
			ft_mlx_pixput(vars, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

int	ft_render(t_vars *vars)
{
	int fd = open("42.fdf", O_RDONLY);
	//int fd = open("mars.fdf", O_RDONLY);
	//int fd = open("pyramide.fdf", O_RDONLY);
	ft_set_black(vars);
	ft_draw_grid(fd, *vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	//ft_bzero(vars->img, vars->win_height * vars->l_len + vars->win_width * (vars->bpp / 8)); 
	return (1);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_vars	vars;

	vars.is_drawn = 0;
	vars.mlx = mlx_init();
	vars.win_width = 1500;
	vars.win_height = 1100;
	vars.margin = 50;
	vars.win = mlx_new_window(vars.mlx, vars.win_width, vars.win_height, "FdF");
	vars.img = mlx_new_image(vars.mlx, vars.win_width, vars.win_height);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bpp, &vars.l_len, &vars.endian);
	mlx_hook(vars.win, 2, 0, ft_event_handle, &vars);
	mlx_loop_hook(vars.mlx, ft_render, &vars);
	mlx_loop(vars.mlx);
}
