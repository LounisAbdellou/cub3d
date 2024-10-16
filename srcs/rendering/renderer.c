/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:48:19 by labdello          #+#    #+#             */
/*   Updated: 2024/10/23 17:43:21 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	get_texture(t_env *env, t_ray ray)
{
	if (!ray.is_v)
	{
		if (ray.angle > 0 && ray.angle < M_PI)
			return (env->assets.n);
		else
			return (env->assets.s);
	}
	else
	{
		if (ray.angle > M_PI / 2 && ray.angle < 3 * M_PI / 2)
			return (env->assets.e);
		else
			return (env->assets.w);
	}
}

void	draw_wall(t_env *env, t_ray ray, double origin, double end)
{
	int			x;
	int			y;
	char		*pixel;
	t_texture	texture;

	x = 0;
	y = 0;
	texture = get_texture(env, ray);
	while (origin < end)
	{
		pixel = texture.addr + (y * texture.line_length + x
				* (texture.bits_per_pixel / 8));
		ft_put_pixel(env, ray.index, origin, *(int *)pixel);
		origin++;
	}
}

void	render_walls(t_env *env, t_point pos)
{
	int		i;
	t_ray	ray;
	double	end;
	double	origin;

	i = 0;
	ray.angle = env->player.angle - (env->fov_rd / 2);
	while (i < env->screen_w)
	{
		ray.index = i;
		init_ray(env, pos, &ray);
		origin = (env->screen_h / 2) - (ray.height / 2);
		end = (env->screen_h / 2) + (ray.height / 2);
		if (end > env->screen_h)
			end = env->screen_h;
		if (origin < 0)
			origin = 0;
		draw_wall(env, ray, origin, end);
		ray.angle += (env->fov_rd / env->screen_w);
		if (ray.angle > M_PI * 2)
			ray.angle -= M_PI * 2;
		i++;
	}
}

void	render_floor_ceiling(t_env *env)
{
	int	i;
	int	j;

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
	t_ray	ray;
	t_point	p2;

	i = 0;
	ray.angle = env->player.angle - (env->fov_rd / 2);
	while (i < env->screen_w)
	{
		init_ray(env, p1, &ray);
		ray.distance /= cos(nor_angle(ray.angle - env->player.angle));
		p2.x = p1.x + (cos(ray.angle) * ray.distance);
		p2.y = p1.y + (sin(ray.angle) * ray.distance);
		ft_draw_line(env, p1, p2, 0xFFFF00);
		ray.angle += (env->fov_rd / env->screen_w);
		if (ray.angle > M_PI * 2)
			ray.angle -= M_PI * 2;
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
