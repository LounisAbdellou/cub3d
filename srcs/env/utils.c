/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:12:47 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/16 15:53:46 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_env(t_env *env)
{
	if (env->map != NULL)
		ft_free_tab(env->map);
	if (env->win != NULL)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx != NULL)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
}

int	destroy(t_env *env)
{
	if (env != NULL)
		free_env(env);
	exit(0);
}

int	handle_keydown(int keycode, t_env *env)
{
	if (keycode == E_KEY_ESCAPE)
		return (destroy(env));
	else if (keycode == E_KEY_FORWARD || keycode == E_KEY_BACKWARD)
		return (move(keycode, env), 1);
	else if (keycode == E_KEY_LEFT || keycode == E_KEY_RIGHT)
		return (move(keycode, env), 1);
	else if (keycode == 65363 || keycode == 65361)
		return (rotate(keycode, env), 1);
	return (0);
}
