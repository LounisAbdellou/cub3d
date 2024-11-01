/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:21:47 by rbouselh          #+#    #+#             */
/*   Updated: 2024/11/01 16:20:05 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_angle(char pos, t_env *env)
{
	if (pos == 'N')
		env->player.angle = (3 * M_PI) / 2;
	if (pos == 'S')
		env->player.angle = M_PI / 2;
	if (pos == 'E')
		env->player.angle = 2 * M_PI;
	if (pos == 'W')
		env->player.angle = M_PI;
}

char	**ft_rgb_split(char *data, int start, char c, t_env *env)
{
	char	*str;
	int		is_ok;
	int		i;

	str = data + start;
	is_ok = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			is_ok++;
		i++;
	}
	if (is_ok != 2)
		handle_error("Invalid RGB format\n", data, env);
	return (ft_split(data + start, c));
}
