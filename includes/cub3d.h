/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:03:59 by labdello          #+#    #+#             */
/*   Updated: 2024/10/06 12:48:40 by solid_42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"

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
}	t_point;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	char	**map;
	int		screen_w;
	int		screen_h;
	t_point	current_pos;
}	t_env;

// ENV
int		destroy(t_env *env);
int		handle_keydown(int keycode, t_env *env);
void	free_env(t_env *env);
void	init_env(t_env *env);
void	return_error(char *error_message, int exit_status, t_env *env);

#endif
