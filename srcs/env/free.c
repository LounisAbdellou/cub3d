/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:50:32 by rbouselh          #+#    #+#             */
/*   Updated: 2024/11/01 15:53:32 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_asset(t_texture txt, t_env *env)
{
	if (txt.path)
		free(txt.path);
	if (txt.ptr)
		mlx_destroy_image(env->mlx, txt.ptr);
}

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
	if (!env->mlx)
		return ;
	free_asset(env->asset.n, env);
	free_asset(env->asset.s, env);
	free_asset(env->asset.e, env);
	free_asset(env->asset.w, env);
	if (env->win != NULL)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx != NULL)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
	free_maps(env);
}
