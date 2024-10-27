/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:09:41 by labdello          #+#    #+#             */
/*   Updated: 2024/10/27 22:52:28 by solid_42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_grid(t_env *env, t_point pos, size_t size, int offset)
{
	size_t	i;
	size_t	j;
	size_t	cell;

	i = 0;
	cell = size / 20;
	(void)pos;
	while (i <= map_height && i <= (size / cell))
	{
		j = 0;
		while (j < map_width * cell && j < size)
		{
			ft_put_pixel(env, (i * cell) + offset, j + offset, 0xFFFFFF);
			j++;
		}
		i++;
	}
	/* i = 0; */
	/* while (i <= map_width) */
	/* { */
	/* 	j = 0; */
	/* 	while (j < map_height * cell && j < size) */
	/* 	{ */
	/* 		ft_put_pixel(env, j + offset, (i * cell) + offset, 0xFFFFFF); */
	/* 		j++; */
	/* 	} */
	/* 	i++; */
	/* } */
}

void	draw_walls(t_env *env, t_point pos, size_t size, int offset)
{
	size_t	i;
	size_t	j;
	size_t	cell;
	t_point	p;

	(void)pos;
	i = 0;
	cell = size / 20;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			if (world_map[i][j] > 0)
			{
				p.x = (j * cell) + offset;
				p.x -= pos.x - (size / 2);
				p.y = (i * cell) + offset;
				p.y -= pos.y - (size / 2);
				if (p.x > (int)size || p.y > (int)size)
					break ;
				ft_draw_square(env, p, cell, 0x0000FF);
			}
			j++;
		}
		i++;
	}
}

void	draw_angle(t_env *env, t_point pos, int size)
{
	t_point	p1;
	t_point	p2;

	p1.x = pos.x + (size / 2);
	p1.y = pos.y + (size / 2);
	p2.x = p1.x + (cos(env->player.angle) * 20);
	p2.y = p1.y + (sin(env->player.angle) * 20);
	ft_draw_line(env, p1, p2, 0xFFFF00);
}

void	draw_player(t_env *env, int offset, int size, int player_size)
{
	t_point	p;

	p.x = (size / 2) + offset;
	p.y = (size / 2) + offset;
	ft_draw_square(env, p, player_size, 0xFF0000);
	draw_angle(env, p, player_size);
}
