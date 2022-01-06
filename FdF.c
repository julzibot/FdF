/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:35:32 by jibot             #+#    #+#             */
/*   Updated: 2022/01/06 16:05:52 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "./libft/libft.h"
#include "get_next_line.h"

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
	int margin;
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
	int abs_or;

	coeff = ((dot2->y_coord - dot1->y_coord) / (dot2->x_coord - dot1->y_coord));
	abs_or = dot1->y_coord - coeff * dot1->x_coord;
	if (x * coeff + abs_or <= y + dot1->thick && x * coeff + abs_or >= y - dot1->thick \
		&& x > dot1->x_coord && x < dot2->x_coord \
		&& y > dot1->y_coord && y < dot2->y_coord)
		return (1);
	return (0);
}

void	ft_draw_line(t_data img, t_dot *dot1, t_dot *dot2, int color)
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
				ft_mlx_pixput(&img, x, y, color);
			y++;
		}
		x++;
	}
}

t_dot	get_file_data(int fd)
{
	static char		*doc_line;
	static int		ycount;
	static int		i;
	t_dot			dot;
	t_dot			empty;
	
	empty.y_coord = 0;
	if (doc_line[i] == '\n' || ycount == 0)
	{
		doc_line = get_next_line(fd);
		printf("%s\n", doc_line);
		if (!doc_line)
			return (empty);
		i = 0;
		ycount++;
	}
	dot.x_coord = i + 1;
	i++;
	dot.y_coord = ycount;
	dot.height = doc_line[i] - 48;
	dot.thick = 1;
	return (dot);
}

t_data	ft_draw_grid(t_data img, int fd)
{
	t_dot	temp_dot1;
	t_dot	temp_dot2;
	
	while (temp_dot1.y_coord != 0)
	{
		temp_dot1 = get_file_data(fd);
		printf("%d %d %d\n", temp_dot1.x_coord, temp_dot1.y_coord, temp_dot1.height);
		temp_dot2 = get_file_data(fd);
		printf("%d %d %d\n", temp_dot1.x_coord, temp_dot1.y_coord, temp_dot1.height);
		ft_draw_line(img, &temp_dot1, &temp_dot2, 0x00FFFFFF);
	}
	return (img);
}

int	ft_render(t_vars *vars)
{
	t_data	img;
	/*t_dot	dot1;
	t_dot	dot2;

	dot1.x_coord = 10;
	dot1.y_coord = 10;
	dot2.x_coord = 400;
	dot2.y_coord = 800;
	dot1.thick = 1;*/

	int fd = open("42.fdf", O_RDONLY);
	img.img = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
	//ft_draw_line(img, &dot1, &dot2, 0x00FFFFFF);
	img = ft_draw_grid(img, fd);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_vars	vars;
	//t_data	img;

	vars.mlx = mlx_init();
	vars.win_width = 1200;
	vars.win_height = 1000;
	vars.win = mlx_new_window(vars.mlx, vars.win_width, vars.win_height, "FdF test");
	//img.img = mlx_new_image(vars.mlx, vars.win_width, vars.win_height);
	//img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
	//mlx_hook(vars.win, 2, 0, ft_event_handle, &vars);
	mlx_loop_hook(vars.mlx, ft_render, &vars);
	mlx_loop(vars.mlx);
}
