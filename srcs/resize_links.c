/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 00:04:52 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/03 19:13:32 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void		resize_links(t_node *n)
{
	t_node	**aux;
	int		i;

	i = 0;
	if (!(aux = (t_node **)malloc(sizeof(t_node *) * (n->n_links + LINK_BUFF))))
		ft_error(NULL);
	while (i < n->n_links)
	{
		aux[i] = (n->links)[i];
		i++;
	}
	free(n->links);
	n->links = aux;
}
