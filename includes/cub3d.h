/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:03:59 by labdello          #+#    #+#             */
/*   Updated: 2024/10/16 16:16:38 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>

# ifndef PATH
#  define PATH "."
# endif

# define TILE_SIZE 30
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4

typedef enum e_key
{
	E_KEY_FORWARD = 119,
	E_KEY_BACKWARD = 115,
	E_KEY_LEFT = 97,
	E_KEY_RIGHT = 100,
	E_KEY_ESCAPE = 65307,
}	t_key;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	double	angle;
	float	fov_angle;
	int		move_x;
	int		move_y;
} t_player;

typedef struct s_ray
{
	double	angle;
	double	distance;
	int		is_wall;
}	t_ray;

typedef struct s_texture
{
	unsigned long	floor;
	int				is_floor;
	unsigned long	ceil;
	int				is_ceil;
	char			*path_n;
	char			*path_s;
	char			*path_e;
	char			*path_w;
}	t_texture;

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
}	t_lst;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	char		**map;
	int			screen_w;
	int			screen_h;
	int			fd;
	t_lst		*lst_map;
	t_player	*player;
	t_texture	*texture;
}	t_env;

// ENV
int		destroy(t_env *env);
int		handle_keydown(int keycode, t_env *env);
void	free_env(t_env *env);
void	init_env(t_env *env);
void	return_error(char *error_message, int exit_status, t_env *env);

// PARSING
int		check_filename(char *path, char *extension);
void	extract_from_file(t_env *env);
int		is_empty_line(char *line);
int		get_type_data(char *line, t_env *env);
int		get_pos_data(char *line);
void	convert_to_map(t_env *env);
int		is_env_set(t_env *env);
void	set_env_path(char *path, int type, t_env *env);
void	set_env_color(int *rgb, int type, t_env *env);
int		handle_extract_error(char *line, t_env *env, int is_sys);
int		handle_data_error(char *line, t_env *env, int why);
t_lst	*lstnew(char *content);
t_lst	*lstlast(t_lst *lst);
int		lstsize(t_lst *lst);
void	lstadd_back(t_lst **lst, t_lst *new);
void	free_lst(t_lst **lst);

#endif
