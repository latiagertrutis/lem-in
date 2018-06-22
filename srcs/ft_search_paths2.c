/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_paths2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:23:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/22 18:03:59 by jagarcia         ###   ########.fr       */
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
	if (len)
		(*len)++;
	return (path);
}

t_path	*realoj(t_path *src, int len)
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

t_map	*make_path(t_path *bfs, int end, int len)
{
	t_map	*conj;
	t_path	*tmp;
	int		i;
	int		j;

	if (!(conj = (t_map *)ft_memalloc(sizeof(t_map) * (end + 1))))
		ft_error("Error malloc ft_search_paths2\n");
	i = 0;
	j = -1;
	while (end)
	{
		if (bfs[len - i].node->end)
		{
			conj[++j].path = new_path(bfs[len - i++].node, NULL, 0);
			tmp = bfs + len - i;
			end--;
			while (!conj[j].path->node->start)
			{
				conj[j].path->prev = new_path(tmp->prev->node, conj[j].path, 0);
				conj[j].path = conj[j].path->prev;
				tmp = tmp->prev;
			}
		}
	}
	return (conj);
}

t_map	*ft_search_paths2(t_data *data)
{
	t_path	*bfs;
	int		max_paths;
	int		len;
	int		i;
	int		j;
	int		end;

	max_paths = data->start->n_links < data->end->n_links ?
		data->start->n_links : data->end->n_links;
	if (!(bfs = (t_path *)ft_memalloc(1000 * sizeof(t_path))))
		ft_error("Error malloc ft_search_paths2\n");
	bfs[0].node = data->start;
	bfs[0].node->ihbt = 1;
	bfs[0].prev = NULL;
	i = 0;
	j = 0;
	len = 0;
	end = 0;
	while (!bfs[i].node->end)
	{
		j = 0;
		while(j < bfs[i].node->n_links)
		{
			if (!bfs[i].node->links[j]->ihbt)
			{
				if (!((len + 1) % 1000))
					bfs = realoj(bfs, len);
				bfs[len++ + 1].node = bfs[i].node->links[j];
				bfs[len].prev = bfs + i;
				bfs[len].node->end ? end++ : (bfs[len].node->ihbt = 1);
			}
			j++;
		}
		i++;
	}
	return (make_path(bfs, end, len));
}

