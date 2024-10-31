/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:51:26 by labdello          #+#    #+#             */
/*   Updated: 2024/10/28 14:54:16 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	get_texture(t_env *env, t_ray ray)
{
	if (!ray.is_v)
	{
		if (ray.angle > 0 && ray.angle < M_PI)
			return (env->asset.n);
		else
			return (env->asset.s);
	}
	else
	{
		if (ray.angle > M_PI / 2 && ray.angle < 3 * M_PI / 2)
			return (env->asset.e);
		else
			return (env->asset.w);
	}
}

int	get_tex_x(t_ray ray, t_texture texture)
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
