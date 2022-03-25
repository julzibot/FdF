/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:39:13 by jibot             #+#    #+#             */
/*   Updated: 2022/03/24 16:41:33 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	ft_height_handle(int keycode, t_vars *vars)
{
	if (keycode == 126)
	{
		vars->max_height += 1;
		if (vars->max_height == 0)
			vars->max_height += 1;
	}
	else if (keycode == 125)
	{
		vars->max_height -= 1;
		if (vars->max_height == 0)
			vars->max_height -= 1;
	}
	else if (keycode == 123)
		vars->render.height -= 0.5;
	else if (keycode == 124)
		vars->render.height += 0.5;
	vars->is_drawn = 0;
	return (keycode);
}

int	ft_key_bonus_handle(int keycode, t_vars *vars)
{
	if (keycode == 0 || keycode == 2)
		vars->move_h -= (keycode - 1) * (vars->render.win_width / 300);
	else if (keycode == 13)
		vars->move_v += (vars->render.win_height / 200);
	else if (keycode == 1)
		vars->move_v -= (vars->render.win_height / 200);
	else if (keycode == 53)
	{
		ft_set_black(vars);
		exit(0);
	}
	else if (keycode == 30)
		vars->render.x_factor += 0.003;
	else if (keycode == 33)
		vars->render.x_factor -= 0.003;
	else if (keycode == 39)
		vars->render.bar_rot -= 0.02;
	else if (keycode == 41)
		vars->render.bar_rot += 0.02;
	else
		ft_height_handle(keycode, vars);
	vars->is_drawn = 0;
	return (keycode);
}

int	ft_key_handle(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		ft_set_black(vars);
		exit(0);
	}
	return (keycode);
}

/*int	ft_move_handle(int x, int y, t_vars *vars)
{
	float	prev_x;
	float	prev_y;

	prev_x = vars->render.xmove;
	prev_y = vars->render.ymove;
	vars->render.xmove = x/1920;
	vars->render.ymove = y/1035;

	if (vars->render.ymove > prev_y)
		vars->render.x_factor += 0.005;
	else if (vars->render.ymove < prev_y)
		vars->render.x_factor -= 0.005;
	vars->is_drawn = 0;
	return (1);
}

int	ft_buttonr_handle(int button, int x, int y, t_vars *vars)
{
	x = 1;
	y = 1;
	if (button == 1)
		return (1);
	return (0);
	vars->is_drawn = 0;
}*/

int	ft_buttonp_handle(int button, int x, int y, t_vars *vars)
{
	x = 1;
	y = 1;
	if (button == 1)
		mlx_hook(vars->win, 4, 0, ft_buttonp_handle, vars);
	if (button == 4)
	{
		vars->render.zoom += 1.5;
		vars->render.height += 0.17;
	}
	else if (button == 5 && vars->render.zoom > -35)
	{
		vars->render.zoom -= 1.5;
		vars->render.height -= 0.17;
	}
	vars->is_drawn = 0;
	return (1);
}
