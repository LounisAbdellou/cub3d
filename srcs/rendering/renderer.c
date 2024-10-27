/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:48:19 by labdello          #+#    #+#             */
/*   Updated: 2024/10/27 22:18:38 by solid_42         ###   ########.fr       */
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

int		get_tex_x(t_ray ray, t_texture texture)
{
	double	x;

	if (!ray.is_v)
		x = (int)fmodf((ray.h_x
			* (texture.width / TILE_SIZE)), texture.width);
	else
		x = (int)fmodf((ray.v_y
			* (texture.width / TILE_SIZE)), texture.width);
	return (x);
}

void	draw_wall(t_env *env, t_ray ray, double origin, double end)
{
	t_point		pos;
	double		tex_pos;
	double		step;
	char		*pixel;
	t_texture	texture;

	texture = get_texture(env, ray);
	step = 1.0 * (texture.height / ray.height);
	tex_pos = (origin - env->screen_h / 2 + ray.height / 2) * step;
	pos.x = get_tex_x(ray, texture);
	while (origin < end)
	{
		pos.y = (int)tex_pos & (texture.height - 1);
		pixel = texture.addr + (pos.y * texture.line_length + pos.x
				* (texture.bits_per_pixel / 8));
		ft_put_pixel(env, ray.index, origin, *(int *)pixel);
		origin++;
		tex_pos += step;
	}
}

void	render_walls(t_env *env, t_point pos)
{
	int		i;
	t_ray	ray;
	t_ray	prev_ray;
	double	end;
	double	origin;

	i = 0;
	ray.angle = env->player.angle - (env->fov_rd / 2);
	while (i < env->screen_w)
	{
		ray.index = i;
		init_ray(env, pos, &ray, &prev_ray);
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
		prev_ray = ray;
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

void	draw_minimap(t_env *env)
{
	t_point	pos;
	int		size;
	int		offset;

	size = 400;
	offset = 20;
	pos.x = offset;
	pos.y = offset;
	ft_draw_square(env, pos, size, 0x000000);
	draw_walls(env, env->player.pos, size, offset);
	draw_grid(env, env->player.pos, size, offset);
	draw_player(env, offset, size, TILE_SIZE / 4);
}

void	render(t_env *env)
{
	env->img.ptr = mlx_new_image(env->mlx, env->screen_w, env->screen_h);
	env->img.addr = mlx_get_data_addr(env->img.ptr, &(env->img.bits_per_pixel),
			&(env->img.line_length), &(env->img.endian));
	render_floor_ceiling(env);
	render_walls(env, env->player.pos);
	draw_minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.ptr, 0, 0);
	mlx_destroy_image(env->mlx, env->img.ptr);
}
