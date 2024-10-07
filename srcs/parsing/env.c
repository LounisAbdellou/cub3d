/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:22:29 by rbouselh          #+#    #+#             */
/*   Updated: 2024/10/31 16:12:27 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_env_set(t_env *env)
{
	int	count;

	count = 0;
	if (env->asset.n.path)
		count++;
	if (env->asset.s.path)
		count++;
	if (env->asset.w.path)
		count++;
	if (env->asset.e.path)
		count++;
	if (env->asset.is_floor)
		count++;
	if (env->asset.is_ceil)
		count++;
	if (count == 6)
		return (1);
	return (0);
}

void	set_env_path(char *path, int type, t_env *env)
{
	if (type == 1)
	{
		if (env->asset.n.path)
			free(env->asset.n.path);
		env->asset.n.path = path;
	}
	else if (type == 2)
	{
		if (env->asset.s.path)
			free(env->asset.s.path);
		env->asset.s.path = path;
	}
	else if (type == 3)
	{
		if (env->asset.w.path)
			free(env->asset.w.path);
		env->asset.w.path = path;
	}
	else if (type == 4)
	{
		if (env->asset.e.path)
			free(env->asset.e.path);
		env->asset.e.path = path;
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
		env->asset.is_floor = 1;
		env->asset.floor = color;
	}
	else if (type == 6)
	{
		env->asset.is_ceil = 1;
		env->asset.ceil = color;
	}
}

void	convert_to_map(t_env *env)
{
	t_lst	*current;
	t_lst	*next;
	int		i;
	int		max_w;

	i = 0;
	max_w = 0;
	current = env->lst_map;
	env->map = ft_calloc(lstsize(current) + 1, sizeof(char *));
	if (!env->map)
		return_error("Malloc failed at map conversion\n", 1, env);
	while (current)
	{
		next = current->next;
		env->map[i] = ft_strdup(current->content);
		if (!env->map[i])
			return_error("Malloc failed at map conversion\n", 1, env);
		if ((int)ft_strlen(env->map[i]) > max_w)
			max_w = (int)ft_strlen(env->map[i]);
		current = next;
		i++;
	}
	env->map_w = max_w;
}

void	convert_to_wmap(t_env *env)
{
	int	i;
	int	j;

	i = 0;
	env->map_h = ft_tablen(env->map);
	env->w_map = ft_calloc(env->map_h + 1, sizeof(int *));
	if (!env->w_map)
		return_error("Malloc failed at map conversion\n", 1, env);
	while (env->map[i])
	{
		env->w_map[i] = ft_calloc(env->map_w + 1, sizeof(int));
		if (!env->w_map[i])
			return_error("Malloc failed at map conversion\n", 1, env);
		j = 0;
		while (env->map[i][j])
		{
			if (env->map[i][j] == '1')
				env->w_map[i][j] = 1;
			j++;
		}
		i++;
	}
}
