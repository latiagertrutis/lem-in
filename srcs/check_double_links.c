/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double_links.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 03:43:26 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/10 03:43:50 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		check_double_links(t_node *node)
{
	int i;
	int j;

	while (node)
	{
		i = 0;
		while (i < node->n_links)
		{
			j = i + 1;
			while (j < node->n_links)
			{
				if (node->links[i]->id == node->links[j++]->id && ((!node->start
					|| !node->links[i]->end) && (!node->end ||
					!node->links[i]->end)))
					ft_cut_and_reset(node, i, NULL, 0);
			}
			i++;
		}
		node = node->next;
	}
}
