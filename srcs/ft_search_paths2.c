/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_paths2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:23:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/27 13:03:56 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_path	*new_path(t_node *node, t_path *next, int *len)
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

static t_path	*realoj(t_path *src, int len)
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

static t_map	*make_path(t_path *bfs, int end, int len)
{
	t_map	*conj;
	t_map	*head;
	t_path	*tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
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
			conj->path = new_path(bfs[len - i].node, NULL, &(conj->len));
			conj->tail = conj->path;
			tmp = bfs + len - i;
			end--;
			while (!conj->path->node->start)
			{
				conj->path->prev = new_path(tmp->prev->node, conj->path, &(conj->len));
				conj->path = conj->path->prev;
				tmp = tmp->prev;
			}
		}
	}
	free(bfs);
	conj = head;
	return (conj);
}

static t_map	*searcher_core(t_path *bfs, int max, int len, int *end)
{
	int	i[3];

	i[0] = -1;
	while (!bfs[++i[0]].node->end)
	{
		i[1] = -1;
		i[2] = 0;
		if (max == bfs[i[0]].node->ihbt + 1)
			while (i[2] < bfs[i[0]].node->n_links && !bfs[i[0]].node->links[i[2]]->end)
				i[2]++;
		while(++i[1] < bfs[i[0]].node->n_links && (i[2] == bfs[i[0]].node->n_links || !i[2]))
		{
			if (!bfs[i[0]].node->links[i[1]]->ihbt && !bfs[i[0]].node->links[i[1]]->start)
			{
				if (!((len + 1) % 1000))
					bfs = realoj(bfs, len);
				bfs[++len].node = bfs[i[0]].node->links[i[1]];
				bfs[len].prev = bfs + i[0];
				if (bfs[len].node->end)
					(*end)++;
				else
					bfs[len].node->ihbt = bfs[i[0]].node->ihbt + 1;
			}
		}
		if (i[0] + 1 > len)
			return (NULL);
	}
	return (make_path(bfs, *end, len));	
}

t_map	*ft_search_paths2(t_node *start, int *end, int *max)
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
	map = searcher_core(bfs, *max, len, &tmp_end);
	*end += tmp_end;
	*max = 0;
	return (map);
}
