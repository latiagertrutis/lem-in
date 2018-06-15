/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 07:54:46 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/12 07:55:17 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_path *ft_new_node(t_path *prev, t_node *src)
{
	t_node	*dst;

	if (!(dst = (t_path *)ft_memalloc(sizeof(t_path))))
		ft_error("ERROR in malloc in ft_new_node\n");
	dst->node = src;
	dst->next = NULL;
	dst->prev = prev;
	return (dst);
}
