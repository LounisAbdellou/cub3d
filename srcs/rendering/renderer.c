/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:48:19 by labdello          #+#    #+#             */
/*   Updated: 2024/10/10 19:38:58 by labdello         ###   ########.fr       */
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
			ft_put_pixel(env, i * offset, j, 0xFFFFFF);
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
			ft_put_pixel(env, j, i * offset, 0xFFFFFF);
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

void	draw_angle(t_env *env, int size)
{
	size_t	len;
	t_point	p1;
	t_point	p2;

	len = 20;
	p1.x = env->player.pos.x + (size / 2);
	p1.y = env->player.pos.y + (size / 2);
	p2.x = round(p1.x + len * cos(env->player.angle * 3.14 / 180));
	p2.y = round(p1.y + len * sin(env->player.angle * 3.14 / 180));
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

void	render(t_env *env)
{
	env->img.ptr = mlx_new_image(env->mlx, env->screen_w, env->screen_h);
	env->img.addr = mlx_get_data_addr(env->img.ptr, &(env->img.bits_per_pixel),
		&(env->img.line_length), &(env->img.endian));
	draw_walls(env, env->offset);
	draw_grid(env, env->offset);
	draw_player(env, env->player.pos.x, env->player.pos.y, env->offset / 4);
	mlx_put_image_to_window(env->mlx, env->win, env->img.ptr, 0, 0);
}
