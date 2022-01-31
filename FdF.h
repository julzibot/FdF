/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:50:15 by jibot             #+#    #+#             */
/*   Updated: 2022/01/18 17:46:05 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <stdio.h>
# include "./libft/libft.h"
# include "get_next_line.h"

typedef struct s_render {
	int	win_width;
	int win_height;
	int margin;
	float seg_len;
	float height;
	float x_factor;
	float y_factor;
	float bar_rot;
	//float disc_rot;
	float zoom;
	float xmove;
	float ymove;
}	t_render;

typedef struct s_data {
  void	*img;
  char	*addr;
  int	bpp;
  int	l_len;
  int	endian;
  char	*img_name;
}	t_data;

typedef struct s_vars {
	t_data		img;
	t_render	render;
	void		*mlx;
	void		*win;
	int			move_h;
	int			move_v;
	int			max_height;
	int			zoom;
	int			is_drawn;
}	t_vars;

typedef struct s_dot {
	float x_coord;
	float y_coord;
	float thick;
	int height;
	int max_height;
}	t_dot;

float	is_grid_seg(int x, int y, t_dot *dot1, t_dot *dot2);
t_dot	*iso_coord(t_dot *dot, t_vars vars);
t_dot	*norm_coord(t_dot *dot, t_vars vars);
void	ft_mlx_pixput(t_vars *data, int x, int y, int color);
int		color_gradient(int x, int y, t_dot dot1, t_dot dot2);
t_vars	ft_draw_line(t_vars img, t_dot dot1, t_dot dot2);
void	ft_set_black(t_vars *vars);
float	ft_min(float a, float b);
float	ft_max(float a, float b);
int		ft_tablen(char **tab);
char	**ft_tabdup(char **data);
int		ft_key_handle(int keycode, t_vars *vars);
int		ft_move_handle(int x, int y, t_vars *vars);
int		ft_buttonp_handle(int button, int x, int y, t_vars *vars);

#endif
