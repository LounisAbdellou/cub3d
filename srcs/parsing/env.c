/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:22:29 by rbouselh          #+#    #+#             */
/*   Updated: 2024/10/16 16:18:21 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_env_set(t_env *env)
{
	int	count;

	count = 0;
	if (env->texture->path_n)
		count++;
	if (env->texture->path_s)
		count++;
	if (env->texture->path_w)
		count++;
	if (env->texture->path_e)
		count++;
	if (env->texture->is_floor)
		count++;
	if (env->texture->is_ceil)
		count++;
	if (count == 6)
		return (1);
	return (0);
}

void	set_env_path(char *path, int type, t_env *env)
{
	if (type == 1)
	{
		if (env->texture->path_n)
			free(env->texture->path_n);
		env->texture->path_n = path;
	}
	else if (type == 2)
	{
		if (env->texture->path_s)
			free(env->texture->path_s);
		env->texture->path_s = path;
	}
	else if (type == 3)
	{
		if (env->texture->path_w)
			free(env->texture->path_w);
		env->texture->path_w = path;
	}
	else if (type == 4)
	{
		if (env->texture->path_e)
			free(env->texture->path_e);
		env->texture->path_e = path;
	}
}

void	set_env_color(int *rgb, int type, t_env *env)
{
	unsigned long	color;
	unsigned long	r;
	unsigned long	g;
	unsigned long	b;

	r = (unsigned long)rgb[0];
	g = (unsigned long)rgb[1];
	b = (unsigned long)rgb[2];
	color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	if (type == 5)
	{
		env->texture->is_floor = 1;
		env->texture->floor = color;
	}
	else if (type == 6)
	{
		env->texture->is_ceil = 1;
		env->texture->ceil = color;
	}
}
