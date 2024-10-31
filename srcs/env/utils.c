/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:12:47 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/31 17:51:38 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy(t_env *env)
{
	if (env != NULL)
		free_env(env);
	exit(0);
}

int	handle_mouse(int x, int y, t_env *env)
{
	int	delta;

	(void)y;
	if (abs(x - env->screen_w / 2) <= 5)
		delta = abs(x - env->screen_w / 2);
	else
		delta = 5;
	if (x > env->screen_w / 2)
		rotate(E_KEY_ARROW_RIGHT, delta, 2, env);
	else if (x < env->screen_w / 2)
		rotate(E_KEY_ARROW_LEFT, delta, 2, env);
	mlx_mouse_move(env->mlx, env->win, env->screen_w / 2, env->screen_h / 2);
	return (1);
}

int	handle_keydown(int keycode, t_env *env)
{
	if (keycode == E_KEY_ESCAPE)
		return (destroy(env));
	else if (keycode == E_KEY_FORWARD || keycode == E_KEY_BACKWARD)
		return (move(keycode, env), 1);
	else if (keycode == E_KEY_LEFT || keycode == E_KEY_RIGHT)
		return (move(keycode, env), 1);
	else if (keycode == E_KEY_ARROW_RIGHT || keycode == E_KEY_ARROW_LEFT)
		return (rotate(keycode, 2, 1, env), 1);
	return (0);
}
