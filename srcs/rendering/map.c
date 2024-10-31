/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:09:41 by labdello          #+#    #+#             */
/*   Updated: 2024/10/31 16:10:22 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_grid(t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (i <= env->map_h)
	{
		j = 0;
		while (j < env->map_w * TILE_SIZE)
		{
			ft_put_pixel(env, i * TILE_SIZE, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	i = 0;
	while (i <= env->map_w)
	{
		j = 0;
		while (j < env->map_h * TILE_SIZE)
		{
			ft_put_pixel(env, j, i * TILE_SIZE, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_walls(t_env *env)
{
	int		i;
	int		j;
	t_point	p;

	i = 0;
	while (i < env->map_h)
	{
		j = 0;
		while (j < env->map_w)
		{
			if (env->w_map[i][j] > 0)
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

void	draw_angle(t_env *env, int size)
{
	t_point	p1;
	t_point	p2;

	p1.x = env->player.pos.x + (size / 2);
	p1.y = env->player.pos.y + (size / 2);
	p2.x = p1.x + (cos(env->player.angle) * 20);
	p2.y = p1.y + (sin(env->player.angle) * 20);
	ft_draw_line(env, p1, p2, 0xFFFF00);
}

void	draw_player(t_env *env, int x, int y, int size)
{
	t_point	p;

	p.x = x;
	p.y = y;
	ft_draw_square(env, p, size, 0xFF0000);
	draw_angle(env, size);
}
