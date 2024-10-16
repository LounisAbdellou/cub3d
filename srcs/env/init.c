/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:08:52 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/18 13:36:57 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_env(t_env *env)
{
	env->mlx = mlx_init();
	mlx_get_screen_size(env->mlx, &env->screen_w, &env->screen_h);
	env->screen_h = env->screen_h - 37;
	env->win = NULL;
	env->map = NULL;
	env->player = ft_calloc(1, sizeof(t_player));
	env->texture = ft_calloc(1, sizeof(t_texture));
	env->lst_map = NULL;
	if (!(env->player) || !(env->texture))
		return_error("Problem on env init\n", 1, env);
}
