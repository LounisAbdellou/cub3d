/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:11:46 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/16 15:51:53 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel(t_env *env, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = env->img.addr + (y * env->img.line_length + x
			* (env->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_line_loop(t_env *env, t_point p1, t_point p2, long color)
{
	int		x;
	float	y;
	float	gradient;

	x = p1.x;
	y = p1.y;
	gradient = (float)(p2.y - p1.y) / (float)(p2.x - p1.x);
	if ((float)(p2.x - p1.x) == 0.0f)
		gradient = 1.f;
	while (x <= p2.x)
	{
		if (env->steep)
		{
			ft_put_pixel(env, (int)y, x, color);
			ft_put_pixel(env, (int)y + 1, x, color);
		}
		else
		{
			ft_put_pixel(env, x, (int)y, color);
			ft_put_pixel(env, x, (int)y + 1, color);
		}
		y += gradient;
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
			ft_put_pixel(env, p.x + i, p.y + j, color);
			j++;
		}
		i++;
	}
}
