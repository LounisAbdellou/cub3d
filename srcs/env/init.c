/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:08:52 by solid_42          #+#    #+#             */
/*   Updated: 2024/11/01 15:52:32 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_tex(t_env *env)
{
	env->asset.n.path = NULL;
	env->asset.n.addr = NULL;
	env->asset.n.ptr = NULL;
	env->asset.s.path = NULL;
	env->asset.s.addr = NULL;
	env->asset.s.ptr = NULL;
	env->asset.e.path = NULL;
	env->asset.e.addr = NULL;
	env->asset.e.ptr = NULL;
	env->asset.w.path = NULL;
	env->asset.w.addr = NULL;
	env->asset.w.ptr = NULL;
	env->asset.is_floor = 0;
	env->asset.is_ceil = 0;
}

void	init_env(t_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
		return_error("Error initializing mlx\n", 1, env);
	mlx_get_screen_size(env->mlx, &env->screen_w, &env->screen_h);
	env->screen_h = env->screen_h - 37;
	env->fov_rd = (FOV * M_PI) / 180;
	env->win = NULL;
	env->map = NULL;
	env->w_map = NULL;
	env->lst_map = NULL;
	init_tex(env);
}
