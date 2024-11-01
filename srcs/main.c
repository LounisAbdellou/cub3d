/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/11/01 16:04:35 by rbouselh         ###   ########.fr       */
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
	mlx_hook(env->win, 17, 1L << 0, destroy, env);
	mlx_key_hook(env->win, handle_keydown, env);
	render(env);
	mlx_loop(env->mlx);
}

void	init_texture(t_env *env, t_texture *texture)
{
	texture->width = 64;
	texture->height = 64;
	texture->ptr = mlx_xpm_file_to_image(env->mlx, texture->path,
			&(texture->width), &(texture->height));
	if (!texture->ptr)
		return_error("Error initializing texture\n", 1, env);
	texture->addr = mlx_get_data_addr(texture->ptr, &(texture->bits_per_pixel),
			&(texture->line_length), &(texture->endian));
	if (!texture->addr)
		return_error("Error initializing texture\n", 1, env);
}

int	main(int ac, char **av)
{
	t_env	env;

	init_env(&env);
	if (ac != 2)
		return_error("Wrong number of arguments\n", 1, &env);
	parse_and_check(av[1], &env);
	init_texture(&env, &(env.asset.n));
	init_texture(&env, &(env.asset.s));
	init_texture(&env, &(env.asset.e));
	init_texture(&env, &(env.asset.w));
	cub3d(&env);
	return (0);
}
