/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:48:19 by labdello          #+#    #+#             */
/*   Updated: 2024/10/16 19:04:19 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays(t_env *env, t_point p1)
{
	int		i;
	int		inter;
	float	angle;
	t_point	p2;

	i = 0;
	angle = env->player.angle - (M_PI / 6);
	while (i < 60)
	{
		inter = get_best_inter(env, p1, angle);
		p2.x = p1.x + (cos(angle) * inter);
		p2.y = p1.y + (sin(angle) * inter);
		ft_draw_line(env, p1, p2, 0xFFFF00);
		angle += DR;
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
	draw_walls(env);
	draw_grid(env);
	draw_player(env, env->player.pos.x, env->player.pos.y, TILE_SIZE / 4);
	draw_rays(env, env->player.pos);
	mlx_put_image_to_window(env->mlx, env->win, env->img.ptr, 0, 0);
	mlx_destroy_image(env->mlx, env->img.ptr);
}
