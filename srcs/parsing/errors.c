/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:27:47 by rbouselh          #+#    #+#             */
/*   Updated: 2024/10/24 14:14:59 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_error(char *msg, char *line, t_env *env)
{
	close(env->fd);
	get_next_line(-1);
	free(line);
	return_error(msg, 1, env);
	return (-1);
}

int	handle_rgb_error(char **extract, char *line, t_env *env)
{
	ft_free_tab(extract);
	handle_error("Invalid RGB format\n", line, env);
	return (-1);
}

int	handle_map_error(char *msg, char **map, t_env *env)
{
	ft_free_tab(map);
	return_error(msg, 1, env);
	return (-1);
}
