/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/10/15 18:59:54 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_and_check(char *input, t_env *env)
{
	if (!check_filename(input, "cub"))
		return_error("Wrong map filename\n", 1, env);
	env->fd = open(input, O_RDONLY);
	if (env->fd < 0)
		return_error("File not exist or bad permission\n", 1, env);
	extract_from_file(env);
}

static void	cub3d(t_env *env)
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

	init_env(&env);
	if (ac != 2)
		return_error("Wrong number of arguments\n", 1, &env);
	parse_and_check(av[1], &env);
	cub3d(&env);
	return (0);
}
