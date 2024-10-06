/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:10:14 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/06 12:16:36 by solid_42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	return_error(char *error_message, int exit_status, t_env *env)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_message, 2);
	if (env != NULL)
		free_env(env);
	exit(exit_status);
}
