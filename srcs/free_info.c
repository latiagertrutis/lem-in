/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 02:29:36 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/10 02:54:38 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void			free_node(t_node *node)
{
	t_node *n_aux;

	while (node)
	{
		n_aux = node;
		node = node->next;
		free(n_aux->name);
		free(n_aux->links);
		free(n_aux);
	}
}

void				free_info(t_node *node, t_map **paths, int min)
{
	t_path	*aux;
	t_path	*aux2;
	t_map	*m_aux;
	int		i;

	free_node(node);
	i = -1;
	while (++i < min)
	{
		while (paths[i])
		{
			aux = paths[i]->tail;
			while (aux)
			{
				aux2 = aux;
				aux = aux->prev;
				free(aux2);
			}
			m_aux = paths[i];
			paths[i] = paths[i]->next;
			free(m_aux);
		}
		free(paths[i]);
	}
	free(paths);
}
