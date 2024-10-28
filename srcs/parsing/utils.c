/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:17:05 by rbouselh          #+#    #+#             */
/*   Updated: 2024/10/28 15:25:42 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSWE", line[i]) && !ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_type_place(char c)
{
	if (c == '0')
		return (1);
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (2);
	if (c == '1' || c == 'X')
		return (0);
	return (-1);
}

int	get_type_data(char *line, t_env *env)
{
	if (is_empty_line(line) && !is_env_set(env))
		return (0);
	if (is_empty_line(line) && is_env_set(env) && !env->lst_map)
		return (0);
	if (!ft_strncmp(line, "NO ", 3))
		return (1);
	if (!ft_strncmp(line, "SO ", 3))
		return (2);
	if (!ft_strncmp(line, "WE ", 3))
		return (3);
	if (!ft_strncmp(line, "EA ", 3))
		return (4);
	if (!ft_strncmp(line, "F ", 2))
		return (5);
	if (!ft_strncmp(line, "C ", 2))
		return (6);
	if (is_map_line(line))
		return (7);
	return (-1);
}

int	get_pos_data(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (0);
	return (i);
}
