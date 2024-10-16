/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:08:52 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/23 17:51:04 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_env(t_env *env)
{
	env->mlx = mlx_init();
	mlx_get_screen_size(env->mlx, &env->screen_w, &env->screen_h);
	env->screen_h = env->screen_h - 37;
	env->fov_rd = (FOV * M_PI) / 180;
	env->win = NULL;
	env->map = NULL;
}
