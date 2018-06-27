/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_funcs2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 13:48:05 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/27 13:51:01 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		ft_finish_conjunt(t_map *(tail_head[2]), t_map **conj, t_node *node, int *cuant)
{
	if (!tail_head[0])
		tail_head[0] = *conj;
	(*conj)->len *= -1;
	if (tail_head[1])
	{
		tail_head[1]->next = *conj;
		(*conj)->prev = tail_head[1];
	}
	*conj = tail_head[0];
	tail_head[0] = NULL;
	tail_head[1] = NULL;
	ft_reset_graf(node, cuant);
	return (0);
}

int		ft_prepare_next(t_map *(tail_head[2]), t_map **conj, int cuant, t_node *node)
{
	if (!tail_head[0])
		tail_head[0] = *conj;
	if (tail_head[1] && tail_head[0] != *conj)
	{
		tail_head[1]->next = *conj;
		(*conj)->prev = tail_head[1];
	}
	tail_head[1] = ft_prepare_graf(node, tail_head[0], cuant - 1, 1);
	*conj = tail_head[1]->next;
	return (1);
}
