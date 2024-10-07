/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:09:41 by labdello          #+#    #+#             */
/*   Updated: 2024/10/16 16:10:19 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_grid(t_env *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i <= map_height)
	{
		j = 0;
		while (j < map_width * TILE_SIZE)
		{
			ft_put_pixel(env, i * TILE_SIZE, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	i = 0;
	while (i <= map_width)
	{
		j = 0;
		while (j < map_height * TILE_SIZE)
		{
			ft_put_pixel(env, j, i * TILE_SIZE, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_walls(t_env *env)
{
	size_t	i;
	size_t	j;
	t_point	p;

	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			if (world_map[i][j] > 0)
			{
				p.x = j * TILE_SIZE;
				p.y = i * TILE_SIZE;
				ft_draw_square(env, p, TILE_SIZE, 0x0000FF);
			}
			j++;
		}
		i++;
	}
}

void	draw_angle(t_env *env)
{
	t_point	p1;
	t_point	p2;
	int		inter_h;
	int		inter_v;

	inter_h = get_h_inter(env, env->player.pos, env->player.angle);
	inter_v = get_v_inter(env, env->player.pos, env->player.angle);
	p1.x = env->player.pos.x;
	p1.y = env->player.pos.y;
	if (inter_v <= inter_h)
	{
		p2.x = p1.x + (cos(env->player.angle) * inter_v);
		p2.y = p1.y + (sin(env->player.angle) * inter_v);
	}
	else
	{
		p2.x = p1.x + (cos(env->player.angle) * inter_h);
		p2.y = p1.y + (sin(env->player.angle) * inter_h);
	}
	ft_draw_line(env, p1, p2, 0xFFFF00);
}

void	draw_player(t_env *env, int x, int y, int size)
{
	t_point	p;

	p.x = x - (size / 2);
	p.y = y - (size / 2);
	ft_draw_square(env, p, size, 0xFF0000);
	draw_angle(env);
}
