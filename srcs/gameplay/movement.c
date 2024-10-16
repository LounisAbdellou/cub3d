/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:54:57 by labdello          #+#    #+#             */
/*   Updated: 2024/10/17 16:16:31 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_hit(float x, float y, t_env *env)
{
	int	x_m;
	int	y_m;

	(void)env;
	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= map_height || x_m >= map_width))
		return (0);
	if (world_map[y_m][x_m] > 0)
		return (0);
	return (1);
}

int	will_collide(t_env *env, int is_straf, int is_increment)
{
	t_point	next_pos;
	int		dx;
	int		dy;
	float	angle;

	angle = env->player.angle;
	if (is_straf)
		angle = env->player.angle - (M_PI / 2);
	dx = round(cos(angle) * 20);
	dy = round(sin(angle) * 20);
	if (is_increment)
	{
		next_pos.x = env->player.pos.x + dx;
		next_pos.y = env->player.pos.y + dy;
	}
	else
	{
		next_pos.x = env->player.pos.x - dx;
		next_pos.y = env->player.pos.y - dy;
	}
	return (!wall_hit(next_pos.x, next_pos.y, env));
}

void	move(int keycode, t_env *env)
{
	int		dx;
	int		dy;
	float	angle;

	angle = env->player.angle;
	if (keycode == E_KEY_LEFT || keycode == E_KEY_RIGHT)
		angle -= (M_PI / 2);
	dx = round(cos(angle) * 5);
	dy = round(sin(angle) * 5);
	if ((keycode == E_KEY_FORWARD || keycode == E_KEY_LEFT)
		&& !will_collide(env, keycode == E_KEY_LEFT, 1))
	{
		env->player.pos.x += dx;
		env->player.pos.y += dy;
	}
	else if ((keycode == E_KEY_BACKWARD || keycode == E_KEY_RIGHT)
		&& !will_collide(env, keycode == E_KEY_RIGHT, 0))
	{
		env->player.pos.x -= dx;
		env->player.pos.y -= dy;
	}
	render(env);
}

void	rotate(int keycode, int distance, int sensi, t_env *env)
{
	if (keycode == E_KEY_ARROW_LEFT)
	{
		env->player.angle -= (DR / sensi) * distance;
		if (env->player.angle < 0)
			env->player.angle += M_PI * 2;
	}
	else if (keycode == E_KEY_ARROW_RIGHT)
	{
		env->player.angle += (DR / sensi) * distance;
		if (env->player.angle > M_PI * 2)
			env->player.angle -= M_PI * 2;
	}
	render(env);
}
