/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:03:59 by labdello          #+#    #+#             */
/*   Updated: 2024/10/24 16:03:03 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "map.h"

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <math.h>

# ifndef PATH
#  define PATH "."
# endif

# define TILE_SIZE 42
# define DR 0.0174533
# define FOV 60

typedef enum e_key
{
	E_KEY_FORWARD = 119,
	E_KEY_BACKWARD = 115,
	E_KEY_LEFT = 97,
	E_KEY_RIGHT = 100,
	E_KEY_ESCAPE = 65307,
	E_KEY_ARROW_LEFT = 65361,
	E_KEY_ARROW_RIGHT = 65363,
}	t_key;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_ray
{
	int		index;
	int		is_v;
	float	angle;
	float	distance;
	float	height;
	float	h_x;
	float	h_y;
	float	v_x;
	float	v_y;
}	t_ray;

typedef struct s_texture
{
	void	*ptr;
	char	*addr;
	char	*path;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_player
{
	float	angle;
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

typedef struct s_asset
{
	t_texture	n;
	t_texture	s;
	t_texture	e;
	t_texture	w;
}	t_asset;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	char		**map;
	int			screen_w;
	int			screen_h;
	int			steep;
	float		fov_rd;
	t_img		img;
	t_player	player;
	t_asset		assets;
}	t_env;

// RENDERING
void	render(t_env *env);
void	ft_draw_line(t_env *env, t_point p1, t_point p2, long color);
void	ft_draw_square(t_env *env, t_point p, int size, long color);
void	ft_put_pixel(t_env *env, int x, int y, int color);
float	get_h_inter(t_env *env, t_point pos, float angl, t_ray *ray);
float	get_v_inter(t_env *env, t_point pos, float angl, t_ray *ray);
void	init_ray(t_env *env, t_point pos, t_ray *ray, t_ray *prev_ray);
float	nor_angle(float angle);

// ENV
int		destroy(t_env *env);
int		handle_mouse(int x, int y, t_env *env);
int		handle_keydown(int keycode, t_env *env);
void	free_env(t_env *env);
void	init_env(t_env *env);
void	return_error(char *error_message, int exit_status, t_env *env);

// GAMEPLAY
int		wall_hit(float x, float y, t_env *env);
void	move(int keycode, t_env *env);
void	rotate(int keycode, int distance, int sensi, t_env *env);

// MAP
void	draw_grid(t_env *env);
void	draw_walls(t_env *env);
void	draw_angle(t_env *env);
void	draw_player(t_env *env, int x, int y, int size);

#endif
