/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:50:53 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/28 23:29:21 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_path		*ft_new_path(t_node *node, t_path *next, int *len)
{
	t_path	*path;

	if (!(path = (t_path *)ft_memalloc(sizeof(t_path))))
		ft_error("Error malloc ft_new_path\n");
	path->next = next;
	path->prev = NULL;
	path->node = node;
	node->ihbt = -1;
	if (len)
		(*len)++;
	return (path);
}

void		ft_prepare_next_node(t_map **conj, t_path **tmp, int *end,
				t_path *ptr)
{
	(*conj)->path = ft_new_path((*ptr).node, NULL, &((*conj)->len));
	(*conj)->tail = (*conj)->path;
	*tmp = ptr;
	(*end)--;
	while (!(*conj)->path->node->start)
	{
		(*conj)->path->prev = ft_new_path((*tmp)->prev->node,
				(*conj)->path, &((*conj)->len));
		(*conj)->path = (*conj)->path->prev;
		(*tmp) = (*tmp)->prev;
	}
}

int			ft_add_node(t_path **bfs, int *len, int i[3])
{
	if (!((*len + 1) % ALGORITHM_BUFF))
		(*bfs) = ft_realoj(*bfs, *len);
	(*bfs)[++(*len)].node = (*bfs)[i[0]].node->links[i[1]];
	(*bfs)[*len].prev = (*bfs) + i[0];
	if ((*bfs)[*len].node->end)
		return (1);
	else
	{
		(*bfs)[*len].node->ihbt = (*bfs)[i[0]].node->ihbt + 1;
		return (0);
	}
}

t_path		*ft_realoj(t_path *src, int len)
{
	t_path *new;

	if (!(new = (t_path *)ft_memalloc(sizeof(t_path) * (len + 1001))))
		ft_error("Error malloc en realoj\n");
	while (len)
	{
		new[len] = src[len];
		len--;
	}
	return (new);
}
