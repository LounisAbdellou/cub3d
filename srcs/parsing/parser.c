/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:33:30 by rbouselh          #+#    #+#             */
/*   Updated: 2024/10/16 16:14:45 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_filename(char *path, char *extension)
{
	char	**explode;
	char	**filename;
	char	*name;
	char	*ext;
	size_t	i;

	if (!path || !path[0])
		return (0);
	explode = ft_split(path, '/');
	if (!explode)
		return (0);
	i = ft_tablen(explode) - 1;
	filename = ft_split(explode[i], '.');
	if (!filename)
		return (ft_free_tab(explode), 0);
	if (ft_tablen(filename) != 2)
		return (ft_free_tab(explode), ft_free_tab(filename), 0);
	name = filename[0];
	ext = filename[1];
	if (ft_strlen(ext) != ft_strlen(extension))
		return (ft_free_tab(explode), ft_free_tab(filename), 0);
	if (ft_strlen(name) > 0 && !ft_strncmp(ext, extension, ft_strlen(ext)))
		return (ft_free_tab(explode), ft_free_tab(filename), 1);
	return (ft_free_tab(explode), ft_free_tab(filename), 0);
}

static int	extract_path(char *data, int start, int type, t_env *env)
{
	int		i;
	int		file_exist;
	char	*extract;

	i = start;
	while (data[i] && !ft_isspace(data[i]))
		i++;
	extract = ft_strndup(data + start, i);
	if (!extract)
		return (handle_extract_error(data, env, 1));
	file_exist = open(extract, O_RDONLY);
	if (file_exist < 0)
		return (handle_data_error(data, env, 1));
	close(file_exist);
	set_env_path(extract, type, env);
	return (1);
}

static int	extract_rgb(char *data, int start, int type, t_env *env)
{
	int		rgb[3];
	int		i;
	int		j;
	char	**extract;
	
	i = 0;
	extract = ft_split(data + start, ',');
	if (!extract)
		return (handle_extract_error(data, env, 1));
	if (ft_tablen(extract) != 3)
		return (ft_free_tab(extract), handle_data_error(data, env, 3));
	while (i < 3)
	{
		j = 0;
		while (extract[i][j] && ft_isdigit(extract[i][j]))
			j++;
		if (extract[i][j] && !ft_isspace(extract[i][j]))
			return (ft_free_tab(extract), handle_data_error(data, env, 3));
		rgb[i] = ft_atoi(extract[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_free_tab(extract), handle_data_error(data, env, 3));
		i++;
	}
	set_env_color(rgb, type, env);
	return (ft_free_tab(extract), 1);
}

static int	extract_data(char *line, t_env *env)
{
	int		type;
	char	*l_map;
	t_lst	*new;

	type = get_type_data(line, env);
	if (type == -1)
		return (handle_extract_error(line, env, 0));
	if (!type)
		return (0);
	if (type < 5)
		return (extract_path(line, get_pos_data(line), type, env));
	if (type < 7)
		return (extract_rgb(line, get_pos_data(line), type, env));
	if (!is_env_set(env))
		return (handle_data_error(line, env, 2));
	l_map = ft_strdup(line);
	if (!l_map)
		return (handle_extract_error(line, env, 1));
	new = lstnew(l_map);
	if (!new)
		return (free(l_map), handle_extract_error(line, env, 1));
	lstadd_back(&(env->lst_map), new);
	return (1);
}

void	extract_from_file(t_env *env)
{
	char	*line;

	line = get_next_line(env->fd);
	if (!line)
	{
		close(env->fd);
		return_error("Empty file\n", 1, env);
	}
	while (line)
	{
		extract_data(line, env);
		free(line);
		line = get_next_line(env->fd);
	}
	close(env->fd);
	convert_to_map(env);
}
