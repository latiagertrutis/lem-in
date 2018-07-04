/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_paths2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:23:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/04 22:07:30 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_map	*make_path(t_path *bfs, int end, int len)
{
	t_map	*conj;
	t_map	*head;
	t_path	*tmp;
	int		i;

	i = -1;
	if (!(conj = (t_map *)ft_memalloc(sizeof(t_map))))
		ft_error("Error malloc ft_search_paths2\n");
	head = conj;
	while (end)
	{
		if (bfs[len - ++i].node->end)
		{
			if (conj->path)
			{
				if (!(conj->next = (t_map *)ft_memalloc(sizeof(t_map))))
					ft_error("Error malloc ft_search_paths2\n");
				conj->next->prev = conj;
				conj = conj->next;
			}
			ft_printf("bfs se va a mover %i alante y %i a detras\n", len, i);
			ft_prepare_next_node(&conj, &tmp, &end, bfs + len - i);
		}
	}
	return (head);
}

static t_map	*searcher_core(t_path **bfs, int max, int len, int *end)
{
	int	i[3];

	i[0] = -1;
	while (!*end)
	{
		i[0]++;
		i[1] = -1;
		i[2] = 0;
		if (max == (*bfs)[i[0]].node->ihbt + 1)
			while (i[2] < (*bfs)[i[0]].node->n_links &&
						!(*bfs)[i[0]].node->links[i[2]]->end)
				i[2]++;
		while (++i[1] < (*bfs)[i[0]].node->n_links && (i[2] ==
				(*bfs)[i[0]].node->n_links || !i[2]))
		{
			if (!(*bfs)[i[0]].node->links[i[1]]->ihbt)
				*end += ft_add_node(bfs, &len, i);
		}
		if (i[0] + 1 > len)
			return (NULL);
	}
	return (make_path((*bfs), *end, len));
}

t_map			*ft_search_paths(t_node *start, int *end, int *max)
{
	t_path	*bfs;
	int		len;
	t_map	*map;
	int		tmp_end;

	tmp_end = 0;
	if (!(bfs = (t_path *)ft_memalloc(1000 * sizeof(t_path))))
		ft_error("Error malloc ft_search_paths2\n");
	bfs[0].node = start;
	bfs[0].node->ihbt = 1;
	bfs[0].prev = NULL;
	len = 0;
	map = searcher_core(&bfs, *max, len, &tmp_end);
	*end += tmp_end;
	*max = 0;
	free(bfs);
	return (map);
}
