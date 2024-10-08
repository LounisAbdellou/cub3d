/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:48:19 by labdello          #+#    #+#             */
/*   Updated: 2024/10/08 22:33:37 by solid_42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map.h"

void	draw_grid(t_env *env, size_t offset)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i <= map_height)
	{
		j = 0;
		while (j < map_width * offset)
		{
			mlx_pixel_put(env->mlx, env->win, i * offset, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	i = 0;
	while (i <= map_width)
	{
		j = 0;
		while (j < map_height * offset)
		{
			mlx_pixel_put(env->mlx, env->win, j, i * offset, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_walls(t_env *env, size_t offset)
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
				p.x = j * offset;
				p.y = i * offset;
				ft_draw_square(env, p, offset, 0x0000FF);
			}
			j++;
		}
		i++;
	}
}

void	draw_direction(t_env *env, t_player *player, size_t offset, size_t size)
{
	size_t	len;
	t_point	p1;
	t_point	p2;

	len = 20;
	p1.x = (player->current_pos.x * offset) + size;
	p1.y = (player->current_pos.y * offset) + size;
	p2.x = p1.x + len * cos(player->direction * 3.14 / 180);
	p2.y = p1.y + len * sin(player->direction * 3.14 / 180);
	ft_draw_line(env, p1, p2, 0xFFFF00);
}

void	draw_player(t_env *env, t_player *player, size_t offset)
{
	t_point	p;
	int		size;

	size = offset / 2;
	p.x = (player->current_pos.x * offset) + (size / 2);
	p.y = (player->current_pos.y * offset) + (size / 2);
	ft_draw_square(env, p, size, 0xFF0000);
	draw_direction(env, player, offset, size);
}

void	render(t_env *env)
{
	t_player	player;
	size_t		offset;

	offset = 42;
	player.current_pos.x = 1;
	player.current_pos.y = 1;
	player.direction = 270;
	draw_walls(env, offset);
	draw_grid(env, offset);
	draw_player(env, &player, offset);
	player.current_pos.x = 4;
	player.current_pos.y = 4;
	player.direction = 30;
	draw_player(env, &player, offset);
}
