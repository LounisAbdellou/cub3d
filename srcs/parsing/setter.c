/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:21:47 by rbouselh          #+#    #+#             */
/*   Updated: 2024/10/31 17:37:36 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_angle(char pos, t_env *env)
{
	if (pos == 'N')
		env->player.angle =  (3 * M_PI) / 2; 
	if (pos == 'S')
		env->player.angle =  M_PI / 2; 
	if (pos == 'E')
		env->player.angle =  2 * M_PI; 
	if (pos == 'W')
		env->player.angle =  M_PI; 
}
