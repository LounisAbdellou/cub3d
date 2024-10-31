/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:12:47 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/30 17:38:56 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_maps(t_env *env)
{
	int	i;

	i = 0;
	if (env->w_map)
	{
		while (env->w_map[i])
		{
			free(env->w_map[i]);
			i++;
		}
		free(env->w_map);
	}
	if (env->map != NULL)
		ft_free_tab(env->map);
	if (env->lst_map != NULL)
		free_lst(&(env->lst_map));
}

void	free_env(t_env *env)
{
	free_maps(env);
	if (env->win != NULL)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx != NULL)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
	if (env->player)
		free(env->player);
	if (env->texture)
	{
		if (env->texture->path_n)
			free(env->texture->path_n);
		if (env->texture->path_s)
			free(env->texture->path_s);
		if (env->texture->path_w)
			free(env->texture->path_w);
		if (env->texture->path_e)
			free(env->texture->path_e);
		free(env->texture);
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
	else if (keycode == E_KEY_FORWARD)
		return (1);
	else if (keycode == E_KEY_BACKWARD)
		return (1);
	else if (keycode == E_KEY_LEFT)
		return (1);
	else if (keycode == E_KEY_RIGHT)
		return (1);
	return (0);
}
