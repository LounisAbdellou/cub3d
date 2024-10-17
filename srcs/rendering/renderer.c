/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:48:19 by labdello          #+#    #+#             */
/*   Updated: 2024/10/17 19:44:52 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void	draw_wall(t_env *env, t_ray ray, int ray_i)
{
	int		limit;
	double	origin;
	double	end;
	double	height;

	limit = ray_i - env->screen_w / FOV;
	ray.distance *= cos(nor_angle(ray.angle - env->player.angle));
	height = (TILE_SIZE / ray.distance) * ((env->screen_w / 2)
			/ tan(FOV_RD / 2));
	while (ray_i >= 0 && ray_i > limit)
	{
		origin = (env->screen_h / 2) - (height / 2);
		end = (env->screen_h / 2) + (height / 2);
		if (end > env->screen_h)
			end = env->screen_h;
		if (origin < 0)
			origin = 0;
		while (origin < end)
			ft_put_pixel(env, ray_i, origin++, 0xFFFFFF);
		ray_i--;
	}
}

void	render_walls(t_env *env, t_point pos)
{
	int		i;
	t_ray	ray;

	i = 0;
	ray.angle = env->player.angle - (FOV_RD / 2);
	while (i < env->screen_w)
	{
		ray.distance = get_best_inter(env, pos, ray.angle);
		draw_wall(env, ray, i);
		// angle += (FOV_RD / env->screen_w);
		ray.angle += DR;
		ray.prev_distance = ray.distance;
		if (ray.angle > M_PI * 2)
			ray.angle -= M_PI * 2;
		i += env->screen_w / FOV;
		// i++;
	}
}

void	render_floor_ceiling(t_env *env)	
{
	int i;
	int j;

	i = 0;
	while (i <= env->screen_h / 2)
	{
		j = 0;
		while (j <= env->screen_w)	
			ft_put_pixel(env, j++, i, 0x383838);
		i++;
	}
	i = env->screen_h / 2;
	while (i <= env->screen_h)
	{
		j = 0;
		while (j <= env->screen_w)	
			ft_put_pixel(env, j++, i, 0x707070);
		i++;
	}
}

void	draw_rays(t_env *env, t_point p1)
{
	int		i;
	int		inter;
	float	angle;
	t_point	p2;

	i = 0;
	angle = env->player.angle - (FOV_RD / 2);
	while (i < env->screen_w)
	{
		inter = get_best_inter(env, p1, angle);
		p2.x = p1.x + (cos(angle) * inter);
		p2.y = p1.y + (sin(angle) * inter);
		ft_draw_line(env, p1, p2, 0xFFFF00);
		angle += (FOV_RD / env->screen_w);
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
		i++;
	}
}

void	render(t_env *env)
{
	env->img.ptr = mlx_new_image(env->mlx, env->screen_w, env->screen_h);
	env->img.addr = mlx_get_data_addr(env->img.ptr, &(env->img.bits_per_pixel),
			&(env->img.line_length), &(env->img.endian));
	// draw_walls(env);
	// draw_grid(env);
	// draw_player(env, env->player.pos.x, env->player.pos.y, TILE_SIZE / 4);
	// draw_rays(env, env->player.pos);
	render_floor_ceiling(env);
	render_walls(env, env->player.pos);
	mlx_put_image_to_window(env->mlx, env->win, env->img.ptr, 0, 0);
	mlx_destroy_image(env->mlx, env->img.ptr);
}
