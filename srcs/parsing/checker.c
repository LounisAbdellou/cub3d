/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:27:43 by rbouselh          #+#    #+#             */
/*   Updated: 2024/10/29 16:49:45 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line(char *line, int type, t_env *env)
{
	int	pos;

	if (type == 7 || type == 0)
		return (0);
	if (type == -1)
	{
		if (is_empty_line(line) && env->lst_map)
			handle_error("Empty line after map declaration\n", line, env);
		if (is_env_set(env))
			handle_error("Invalid charactere in map\n", line, env);
		return (1);
	}
	pos = get_pos_data(line);
	if (!pos)
		handle_error("No data in definition line\n", line, env);
	while (line[pos] && !ft_isspace(line[pos]))
		pos++;
	if (!is_empty_line(line + pos))
		handle_error("Invalid charactere after definition line\n", line, env);
	return (0);
}

static int	flood_fill(char **map, int x, int y, int tablen)
{
	if (y < 0 || y >= tablen || x < 0 || map[y][x] == '1' || map[y][x] == 'X')
		return (0);
	if (get_type_place(map[y][x]) && (y == tablen - 1 || y == 0 || x == 0))
		return (1);
	if (get_type_place(map[y][x]) && get_type_place(map[y][x + 1]) == -1)
		return (1);
	if (get_type_place(map[y][x]) && get_type_place(map[y][x - 1]) == -1)
		return (1);
	if (get_type_place(map[y][x]) && get_type_place(map[y + 1][x]) == -1)
		return (1);
	if (get_type_place(map[y][x]) && get_type_place(map[y - 1][x]) == -1)
		return (1);
	map[y][x] = 'X';
	if (flood_fill(map, x + 1, y, tablen))
		return (1);
	if (flood_fill(map, x - 1, y, tablen))
		return (1);
	if (flood_fill(map, x, y + 1, tablen))
		return (1);
	if (flood_fill(map, x, y - 1, tablen))
		return (1);
	return (0);
}

static void	is_map_close(char **map, t_env *env)
{
	int	i;
	int	j;
	int	tablen;

	i = 0;
	tablen = ft_tablen(map);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (flood_fill(map, j, i, tablen))
					handle_map_error("Unclosed map\n", map, env);
			}
			j++;
		}
		i++;
	}
}

static int	is_spawn_line(char *line, int y, t_env *env, char **map)
{
	int	x;
	int	spawn;

	x = 0;
	spawn = 0;
	while (line[x])
	{
		if (line[x] == 'N' || line[x] == 'W' || line[x] == 'E'
			|| line[x] == 'S')
		{
			env->player->pos_x = x;
			env->player->pos_y = y;
			spawn++;
		}
		x++;
	}
	if (spawn == 1)
		return (1);
	if (spawn > 1)
		handle_map_error("Multiple spawn in map\n", map, env);
	return (0);
}

void	check_map(t_env *env)
{
	char	**map;
	int		i;
	int		spawn;

	map = ft_calloc(ft_tablen(env->map) + 1, sizeof(char *));
	if (!map)
		return_error("Malloc failed\n", 1, env);
	i = 0;
	spawn = 0;
	while (env->map[i])
	{
		if (spawn > 1)
			handle_map_error("Multiple spawn in map\n", map, env);
		spawn += is_spawn_line(env->map[i], i, env, map);
		map[i] = ft_strdup(env->map[i]);
		if (!map[i])
			handle_map_error("Malloc failed\n", map, env);
		i++;
	}
	if (spawn != 1)
		handle_map_error("No spawn in map\n", map, env);
	is_map_close(map, env);
	ft_free_tab(map);
}
