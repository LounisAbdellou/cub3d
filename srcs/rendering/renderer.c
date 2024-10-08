/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:48:19 by labdello          #+#    #+#             */
/*   Updated: 2024/10/08 19:47:56 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map.h"

void	draw_square(t_env *env, double x, double y, size_t offset, long color)
{
	size_t	i;
	size_t	j;

	i = x * offset;
	while (i < (x + 1) * offset)
	{
		j = y * offset;
		while (j < (y + 1) * offset)
		{
			mlx_pixel_put(env->mlx, env->win, i, j, color);
			j++;
		}
		i++;
	}
}

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

	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			if (world_map[i][j] > 0)
				draw_square(env, j, i, offset, 0x0000FF);
			j++;
		}
		i++;
	}
}

#include <math.h>
static void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	ft_draw_line_loop(t_point s, t_point e, t_env *env)
{
	float	inter_y;
	int		x;

	inter_y = (float)s.y;
	x = s.x;
	while (x <= e.x)
	{
		if (env->steep)
		{
			mlx_pixel_put(env->mlx, env->win, (int)inter_y, x, 0xFFFF00);
			mlx_pixel_put(env->mlx, env->win, (int)inter_y + 1, x, 0xFFFF00);
		}
		else
		{
			mlx_pixel_put(env->mlx, env->win, x, (int)inter_y, 0xFFFF00);
			mlx_pixel_put(env->mlx, env->win, x, (int)inter_y + 1, 0xFFFF00);
		}
		x++;
	}
}

void	ft_draw_line(t_point s, t_point e, t_env *env)
{
	float	dy;
	float	dx;

	env->steep = ft_abs(e.y - s.y) > ft_abs(e.x - s.x);
	if (env->steep)
	{
		ft_swap(&s.x, &s.y);
		ft_swap(&e.x, &e.y);
	}
	if (s.x > e.x)
	{
		ft_swap(&s.x, &e.x);
		ft_swap(&s.y, &e.y);
		s.reverse = 1;
	}
	dx = (float)(e.x - s.x);
	dy = (float)(e.y - s.y);
	ft_draw_line_loop(s, e, env);
}

void	draw_direction(t_env *env, t_player *player, size_t offset, size_t size)
{
	size_t	len;
	t_point	p1;
	t_point	p2;

	len = 10;
	p1.x = (player->current_pos.x * offset) + size;
	p1.y = (player->current_pos.y * offset) + size;
	p2.x = p1.x + len * cos(player->direction * 3.14 / 180);
	p2.y = p1.y + len * sin(player->direction * 3.14 / 180);
	ft_draw_line(p1, p2, env);
}

void	draw_player(t_env *env, t_player *player, size_t offset)
{
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	size = offset / 2;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(env->mlx,
				env->win,
				i + (player->current_pos.x * offset) + (size / 2),
				j + (player->current_pos.y * offset) + (size / 2),
				0xFF0000);
			j++;
		}
		i++;
	}
	draw_direction(env, player, offset, size);
}

void	render(t_env *env)
{
	t_player	player;
	size_t		offset;

	offset = 32;
	player.current_pos.x = 2;
	player.current_pos.y = 2;
	player.direction = 270;
	draw_walls(env, offset);
	draw_grid(env, offset);
	draw_player(env, &player, offset);
	player.current_pos.x = 4;
	player.current_pos.y = 4;
	player.direction = 30;
	draw_player(env, &player, offset);
}
