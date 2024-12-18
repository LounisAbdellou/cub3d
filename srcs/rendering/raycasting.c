/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:04:57 by labdello          #+#    #+#             */
/*   Updated: 2024/10/31 16:10:42 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

float	get_h_inter(t_env *env, t_point pos, float angl, t_ray *ray)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(pos.y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = pos.x + (h_y - pos.y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0)
		|| (!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, env))
	{
		h_x += x_step;
		h_y += y_step;
	}
	ray->h_x = h_x;
	ray->h_y = h_y;
	return (sqrt(pow(h_x - pos.x, 2) + pow(h_y - pos.y, 2)));
}

float	get_v_inter(t_env *env, t_point pos, float angl, t_ray *ray)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(pos.x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = pos.y + (v_x - pos.x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0)
		|| (!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, env))
	{
		v_x += x_step;
		v_y += y_step;
	}
	ray->v_x = v_x;
	ray->v_y = v_y;
	return (sqrt(pow(v_x - pos.x, 2) + pow(v_y - pos.y, 2)));
}

void	init_ray(t_env *env, t_point pos, t_ray *ray, t_ray *prev_ray)
{
	int		inter_h;
	int		inter_v;
	float	angle;

	ray->is_v = 0;
	angle = ray->angle;
	inter_h = get_h_inter(env, pos, angle, ray);
	inter_v = get_v_inter(env, pos, angle, ray);
	if (inter_v <= inter_h)
	{
		ray->distance = inter_v * cos(nor_angle(angle - env->player.angle));
		ray->is_v = 1;
	}
	else
		ray->distance = inter_h * cos(nor_angle(angle - env->player.angle));
	if (inter_v == inter_h)
		ray->is_v = prev_ray->is_v;
	ray->height = (TILE_SIZE / ray->distance) * ((env->screen_w / 2)
			/ tan(env->fov_rd / 2));
}
