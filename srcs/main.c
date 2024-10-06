/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/10/06 12:40:49 by solid_42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(t_env *env)
{
	env->win = mlx_new_window(env->mlx, env->screen_w, env->screen_h, "cub3d");
	if (!env->win)
		return_error("Error initializing window\n", 1, env);
	mlx_hook(env->win, 2, 1L << 0, handle_keydown, env);
	mlx_hook(env->win, 17, 1L << 0, destroy, env);
	mlx_loop(env->mlx);
}

int	main(int ac, char **av)
{
	t_env	env;

	(void)av;
	init_env(&env);
	if (ac != 2)
		return_error("Wrong number of arguments\n", 1, &env);
	cub3d(&env);
	return (0);
}
