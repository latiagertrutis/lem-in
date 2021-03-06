/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cuantity_of_ants.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 19:51:02 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/11 03:05:34 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	node_sumatory(t_map *conj, int len)
{
	int sum;
	int i;

	i = 0;
	sum = 0;
	while (i < len && conj)
	{
		sum += conj->len;
		conj = conj->next;
		i++;
	}
	return (sum);
}

int			ft_cuantity_of_ants(t_map *a, t_map *b, int a_len, int b_len)
{
	return (b_len * node_sumatory(a, a_len) -
						a_len * node_sumatory(b, b_len));
}
/*
** a_len & b_len is the cuantity of paths a set has
** a->len & b->len is the number of nodes each path has
*/
