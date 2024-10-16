/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:27:47 by rbouselh          #+#    #+#             */
/*   Updated: 2024/10/16 16:18:46 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_identifier(char *line)
{
	if (line[0] == 'N' && line[1] != 'O')
		return (2);
	if (line[0] == 'S' && line[1] != 'O')
		return (3);
	if (line[0] == 'W' && line[1] != 'E')
		return (4);
	if (line[0] == 'E' && line[1] != 'A')
		return (5);
	if (line[0] == 'F' && line[1] != ' ')
		return (6);
	if (line[0] == 'C' && line[1] != ' ')
		return (7);
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		return (0);
	if (line[0] == 'C' || line[0] == 'F')
		return (0);
	return (1);
}

static void	return_extract_error(int why, char *line, t_env *env)
{
	if (line)
		free(line);
	if (why == 1)
		return_error("Empty line after map declaration\n", 1, env);
	if (why == 2)
		return_error("Invalid identifier\n", 1, env);
	if (why == 3)
		return_error("No data in definition line\n", 1, env);
	if (why == 4)
		return_error("Invalid charactere after texture definition\n", 1, env);
	if (why == 5)
		return_error("File cannot be open\n", 1, env);
	if (why == 6)
		return_error("Missing information in map\n", 1, env);
	if (why == 7)
		return_error("Color must be in rgb format\n", 1, env);
	return_error("Malloc failed\n", 1, env);
}

int	handle_extract_error(char *line, t_env *env, int is_sys)
{
	int	i;
	int	pos;

	close(env->fd);
	if (is_sys)
		return_extract_error(0, line, env);
	if (is_empty_line(line))
		return_extract_error(1, line, env);
	pos = get_pos_data(line);
	i = pos;
	if (check_identifier(line))
		return_extract_error(2, line, env);
	if (!pos)
		return_extract_error(3, line, env);
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (!is_empty_line(line + i))
		return_extract_error(4, line, env);
	return (-1);
}

int	handle_data_error(char *line, t_env *env, int why)
{
	close(env->fd);
	if (why == 1)
		return_extract_error(5, line, env);
	if (why == 2)
		return_extract_error(6, line, env);
	if (why == 3)
		return_extract_error(7, line, env);
	return (-1);
}
