/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:03:59 by labdello          #+#    #+#             */
/*   Updated: 2024/10/10 19:34:38 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <math.h>

# ifndef PATH
#  define PATH "."
# endif

typedef enum e_key
{
	E_KEY_FORWARD = 119,
	E_KEY_BACKWARD = 115,
	E_KEY_LEFT = 97,
	E_KEY_RIGHT = 100,
	E_KEY_ESCAPE = 65307,
}	t_key;

typedef struct s_point
{
	int	x;
	int	y;
	int	reverse;
}	t_point;

typedef struct s_player
{
	int		angle;
	t_point	pos;
}	t_player;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	char		**map;
	int			screen_w;
	int			screen_h;
	int			offset;
	int			steep;
	t_img		img;
	t_player	player;
}	t_env;

// RENDERING
void	render(t_env *env);
void	ft_draw_line(t_env *env, t_point p1, t_point p2, long color);
void	ft_draw_square(t_env *env, t_point p, int size, long color);
void	ft_put_pixel(t_env *env, int x, int y, int color);

// ENV
int		destroy(t_env *env);
int		handle_keydown(int keycode, t_env *env);
void	free_env(t_env *env);
void	init_env(t_env *env);
void	return_error(char *error_message, int exit_status, t_env *env);

#endif
