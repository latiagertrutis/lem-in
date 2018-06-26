/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_funcs1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:00:34 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/26 18:07:46 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lem-in.h"

void	ft_assign_prev(t_map *map, t_map *prev)
{
	if (prev)
	{
		prev->next = map;
		map->prev = prev;
	}
}

int ft_no_more_paths(t_map *map, int *cuant)
{
	int tmp;
	
	if (!*cuant)
	{
		tmp = map->len;
		ft_destroy_path(map, 0);
		return (tmp);
	}
	return (0);
}

void	ft_finish_conj(t_map **conj, t_node *node, int *cuant, int i)
{
	(*conj)->len *= -1;
	while ((*conj)->prev)
		(*conj) = (*conj)->prev;
	ft_reset_graf(node, cuant);
	i = 0;
}

void ft_no_path(t_map **conj, t_map **prev, t_node *node, int cuant)
{
	(*conj) = *prev;
	*prev = NULL;
	ft_prepare_graf(node, (*conj), cuant, 0);
	if (cuant)
		ft_destroy_path((*conj), cuant + 1);
}

int	ft_prepare_next_path(t_map **conj, t_node *node, int cuant, t_map **prev)
{
	ft_prepare_graf(node, *conj, cuant, 1);
	(*prev) = *conj;
	*conj = (*conj)->next;
	return (0);
}
