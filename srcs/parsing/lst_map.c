/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:43:11 by rbouselh          #+#    #+#             */
/*   Updated: 2024/10/28 15:13:18 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_lst	*lstnew(char *content)
{
	t_lst	*element;

	element = (t_lst *)malloc(sizeof(t_lst));
	if (!element)
		return (NULL);
	element->next = NULL;
	element->content = content;
	return (element);
}

t_lst	*lstlast(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*last_element;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last_element = lstlast(*(lst));
		last_element->next = new;
	}
}

void	free_lst(t_lst **lst)
{
	t_lst	*current;
	t_lst	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	return ;
}

void	convert_to_map(t_env *env)
{
	t_lst	*current;
	t_lst	*next;
	int		i;

	i = 0;
	current = env->lst_map;
	while (current)
	{
		current = current->next;
		i++;
	}
	env->map = ft_calloc(i + 1, sizeof(char *));
	if (!env->map)
		return_error("Malloc failed at map conversion\n", 1, env);
	i = 0;
	current = env->lst_map;
	while (current)
	{
		next = current->next;
		env->map[i] = ft_strdup(current->content);
		if (!env->map[i])
			return_error("Malloc failed at map conversion\n", 1, env);
		current = next;
		i++;
	}
}
