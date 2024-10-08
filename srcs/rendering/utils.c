/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:11:46 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/08 22:30:36 by solid_42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_line_loop(t_env *env, t_point p1, t_point p2, long color)
{
	int	x;
	int	y;

	x = p1.x;
	y = p1.y;
	while (x <= p2.x)
	{
		if (env->steep)
		{
			mlx_pixel_put(env->mlx, env->win, y, x, color);
			mlx_pixel_put(env->mlx, env->win, y + 1, x, color);
		}
		else
		{
			mlx_pixel_put(env->mlx, env->win, x, y, color);
			mlx_pixel_put(env->mlx, env->win, x, y + 1, color);
		}
		x++;
	}
}

void	ft_draw_line(t_env *env, t_point p1, t_point p2, long color)
{
	env->steep = ft_abs(p2.y - p1.y) > ft_abs(p2.x - p1.x);
	if (env->steep)
	{
		ft_swap(&p1.x, &p1.y);
		ft_swap(&p2.x, &p2.y);
	}
	if (p1.x > p2.x)
	{
		ft_swap(&p1.x, &p2.x);
		ft_swap(&p1.y, &p2.y);
		p1.reverse = 1;
	}
	ft_draw_line_loop(env, p1, p2, color);
}

void	ft_draw_square(t_env *env, t_point p, int size, long color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(env->mlx, env->win, p.x + i, p.y + j, color);
			j++;
		}
		i++;
	}
}
