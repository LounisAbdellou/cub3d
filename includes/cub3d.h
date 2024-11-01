/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:03:59 by labdello          #+#    #+#             */
/*   Updated: 2024/11/01 16:19:05 by rbouselh         ###   ########.fr       */
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

# define TILE_SIZE 100
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

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
}	t_lst;

typedef struct s_point {
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
	t_texture		n;
	t_texture		s;
	t_texture		e;
	t_texture		w;
	int				is_floor;
	int				is_ceil;
	unsigned long	floor;
	unsigned long	ceil;
}	t_asset;

typedef struct s_player
{
	t_point	pos;
	float	angle;
}	t_player;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	char		**map;
	int			**w_map;
	int			map_w;
	int			map_h;
	int			screen_w;
	int			screen_h;
	int			fd;
	t_lst		*lst_map;
	int			steep;
	float		fov_rd;
	t_img		img;
	t_player	player;
	t_asset		asset;
}	t_env;

// RENDERING
int			get_tex_x(t_ray ray, t_texture texture);
void		render(t_env *env);
void		ft_draw_line(t_env *env, t_point p1, t_point p2, long color);
void		ft_draw_square(t_env *env, t_point p, int size, long color);
void		init_ray(t_env *env, t_point pos, t_ray *ray, t_ray *prev_ray);
void		ft_put_pixel(t_env *env, int x, int y, int color);
float		get_h_inter(t_env *env, t_point pos, float angl, t_ray *ray);
float		get_v_inter(t_env *env, t_point pos, float angl, t_ray *ray);
float		nor_angle(float angle);
t_texture	get_texture(t_env *env, t_ray ray);

// ENV
int			destroy(t_env *env);
int			handle_keydown(int keycode, t_env *env);
void		free_env(t_env *env);
void		init_env(t_env *env);
void		return_error(char *error_message, int exit_status, t_env *env);

// GAMEPLAY
int			wall_hit(float x, float y, t_env *env);
void		move(int keycode, t_env *env);
void		rotate(int keycode, int distance, int sensi, t_env *env);

// PARSING
int			check_filename(char *path, char *extension);
void		extract_from_file(t_env *env);
int			is_empty_line(char *line);
int			is_map_line(char *line);
int			get_type_data(char *line, t_env *env);
int			get_pos_data(char *line);
void		convert_to_map(t_env *env);
void		convert_to_wmap(t_env *env);
int			is_env_set(t_env *env);
void		set_env_path(char *path, int type, t_env *env);
void		set_env_color(int *rgb, int type, t_env *env);
int			handle_error(char *msg, char *line, t_env *env);
int			handle_rgb_error(char **extract, char *line, t_env *env);
int			handle_map_error(char *msg, char **map, t_env *env);
int			check_line(char *line, int type, t_env *env);
int			get_type_place(char c);
void		check_map(t_env *env);
void		set_player_angle(char pos, t_env *env);
char		**ft_rgb_split(char *data, int start, char c, t_env *env);

// LST_MAP
t_lst		*lstnew(char *content);
t_lst		*lstlast(t_lst *lst);
int			lstsize(t_lst *lst);
void		lstadd_back(t_lst **lst, t_lst *new);
void		free_lst(t_lst **lst);

#endif
