/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cuantity_of_ants.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 19:51:02 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/18 20:04:23 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	node_sumatory(t_conj *conj)
{
	int sum;
	int i;

	i = 0;
	sum = 0;
	while (i < conj->cuant)
		sum += conj->path[i++]->len;
	return (sum);
}

int		ft_cuantity_of_ants(t_conj *a, t_conj *b)
{
	return (ft_abs(b->cuant * node_sumatory(a) - a->cuant * node_sumatory(b)));
}
