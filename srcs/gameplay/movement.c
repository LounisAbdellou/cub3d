/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:54:57 by labdello          #+#    #+#             */
/*   Updated: 2024/10/31 11:04:04 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_hit(float x, float y, t_env *env)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= env->map_h || x_m >= env->map_w))
		return (0);
	if (env->w_map[y_m][x_m] > 0)
		return (0);
	return (1);
}

int	will_collide(t_env *env, t_point pos)
{
	int	offset;

	offset = TILE_SIZE / 2;
	pos.x -= offset / 4;
	pos.y -= offset / 4;
	if (!wall_hit(pos.x, pos.y, env))
		return (1);
	else if (!wall_hit(pos.x + offset, pos.y, env))
		return (1);
	else if (!wall_hit(pos.x, pos.y + offset, env))
		return (1);
	else if (!wall_hit(pos.x + offset, pos.y + offset, env))
		return (1);
	return (0);
}

void	move(int keycode, t_env *env)
{
	float	angle;
	t_point	next_pos;

	angle = env->player.angle;
	next_pos.x = env->player.pos.x;
	next_pos.y = env->player.pos.y;
	if (keycode == E_KEY_LEFT || keycode == E_KEY_RIGHT)
		angle -= (M_PI / 2);
	if (keycode == E_KEY_FORWARD || keycode == E_KEY_LEFT)
	{
		next_pos.x += round(cos(angle) * 5);
		next_pos.y += round(sin(angle) * 5);
		if (will_collide(env, next_pos))
			return ;
	}
	else if (keycode == E_KEY_BACKWARD || keycode == E_KEY_RIGHT)
	{
		next_pos.x -= round(cos(angle) * 5);
		next_pos.y -= round(sin(angle) * 5);
		if (will_collide(env, next_pos))
			return ;
	}
	env->player.pos.x = next_pos.x;
	env->player.pos.y = next_pos.y;
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
