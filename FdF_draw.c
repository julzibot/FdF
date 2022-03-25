/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:40:58 by jibot             #+#    #+#             */
/*   Updated: 2022/03/24 16:16:12 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	draw_x(t_vars *vars, char **line_data, int ycount)
{
	int		i;
	t_dot	temp_dot1;
	t_dot	temp_dot2;
	float	seg;

	i = -1;
	seg = vars->render.seg_len;
	temp_dot1.max_height = vars->max_height;
	while (line_data && line_data[++i])
	{
		temp_dot1.height = ft_atoi(line_data[i]);
		temp_dot1.x_coord = seg * (i + 1) + vars->render.margin;
		temp_dot1.y_coord = seg * ycount + vars->render.margin;
		temp_dot1.thick = 1;
		if (line_data[i + 1])
		{
			temp_dot2.height = ft_atoi(line_data[i + 1]);
			temp_dot2.x_coord = seg * (i + 2) + vars->render.margin;
			temp_dot2.y_coord = seg * ycount + vars->render.margin;
		}
		else
			temp_dot2 = temp_dot1;
		ft_draw_line(*vars, *iso_coord(&temp_dot1, *vars), \
		*iso_coord(&temp_dot2, *vars));
	}
}

void	damn(t_vars *vars, char *prev_data, t_dot *temp_dot1, t_dot *temp_dot2)
{
	float	seg;

	seg = vars->render.seg_len;
	temp_dot2->height = ft_atoi(prev_data);
	temp_dot2->x_coord += seg * vars->render.x_factor \
	* vars->render.bar_rot;
	temp_dot2->y_coord -= seg * vars->render.y_factor \
	+ vars->render.height * vars->render.x_factor \
	* (temp_dot2->height - temp_dot1->height);
}

void	draw_y(t_vars *vars, char **line_data, char **prev_data, int ycount)
{
	int		i;
	t_dot	temp_dot1;
	t_dot	temp_dot2;
	float	seg;

	i = -1;
	seg = vars->render.seg_len;
	temp_dot1.max_height = vars->max_height;
	while (line_data && line_data[++i] && ycount > 0)
	{
		vars->render.y_factor = ft_sqrt(1 - vars->render.x_factor \
		* vars->render.x_factor);
		temp_dot1.height = ft_atoi(line_data[i]);
		temp_dot1.x_coord = seg * (i + 1) + vars->render.margin;
		temp_dot1.y_coord = seg * ycount + vars->render.margin;
		temp_dot1.thick = 1;
		temp_dot2 = *iso_coord(&temp_dot1, *vars);
		if (prev_data[i])
			damn(vars, prev_data[i], &temp_dot1, &temp_dot2);
		ft_draw_line(*vars, temp_dot2, temp_dot1);
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
	vars->render.seg_len = ((vars->render.win_width \
	- 2 * vars->render.margin) / (2 * ft_tablen(line_data))) \
	+ vars->render.zoom;
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
