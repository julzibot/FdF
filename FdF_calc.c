/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:45:01 by jibot             #+#    #+#             */
/*   Updated: 2022/01/15 16:27:27 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

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

t_dot	*iso_coord(t_dot *dot, t_vars vars)
{
	float	x;
	float	y;
	float	y_factor;

	x = dot->x_coord;
	y = dot->y_coord;
	y_factor = ft_sqrt(1 - vars.render.x_factor * vars.render.x_factor);
	dot->x_coord = vars.render.x_factor * (x - y) * vars.render.bar_rot + vars.move_h - (6 * vars.render.margin);
	dot->y_coord = y_factor * (x + y) - (vars.render.height * vars.render.x_factor * dot->height) + vars.move_v;
	return (dot);
}

/*t_dot	*norm_coord(t_dot *dot, t_vars vars)
{
	float	x;
	float	y;
	float	y_factor;

	y_factor = ft_sqrt(1 - vars.render.x_factor * vars.render.x_factor);
	x = dot->x_coord - vars.move_h + (6 * vars.render.margin);
	y = dot->y_coord + (4 * vars.render.x_factor * dot->height) - vars.move_v;
	dot->x_coord = y_factor * (y / y_factor + x / vars.render.x_factor);
	dot->y_coord = y_factor * (y / y_factor - x / vars.render.x_factor);
	return (dot);
}*/
