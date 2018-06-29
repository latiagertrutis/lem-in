/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_paths2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:23:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/29 18:09:10 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_path	*ini_bfs(int *i, int *len, t_node *start)
{
	t_path *bfs;

	if (!(bfs = (t_path *)ft_memalloc(1000 * sizeof(t_path))))
		ft_error("Error malloc ft_search_paths2\n");
	bfs[0].node = start;
	bfs[0].node->ihbt = 1;
	bfs[0].prev = NULL;
	*i = -1;
	*len = 0;
	return (bfs);
}

static int		search_path(t_node *start)
{
	t_path	*bfs;
	int		len;
	int		i;
	int		j;

	bfs = ini_bfs(&i, &len, start);
	while (++i <= len)
	{
		j = -1;
		while (++j < bfs[i].node->n_links)
		{
			if (!bfs[i].node->links[j]->ihbt && !bfs[i].node->links[j]->start)
			{
				if (!((len + 1) % ALGORITHM_BUFF))
					bfs = ft_realoj(bfs, len);
				bfs[++len].node = bfs[i].node->links[j];
				bfs[len].prev = bfs + i;
				if (bfs[len].node->end)
				{
					free(bfs);
					return (1);
				}
				bfs[len].node->ihbt = 1;
			}
		}
	}
	free(bfs);
	return (0);
}

static void		cut_and_reset(t_node *true_start, int pos,
								t_node *node, int reset)
{
	if (reset)
	{
		while (node)
		{
			node->ihbt = 0;
			node = node->next;
		}
	}
	else
	{
		while (pos + 1 < true_start->n_links)
		{
			true_start->links[pos] = true_start->links[pos + 1];
			pos++;
		}
		true_start->n_links--;
		true_start->links[pos] = NULL;
	}
}

static void		check_double_links(t_node *node)
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
			|| !node->links[i]->end) && (!node->end || !node->links[i]->end)))
					cut_and_reset(node, i, NULL, 0);
			}
			i++;
		}
		node = node->next;
	}
}

void			ft_depure_graf(t_data *data, t_node *node)
{
	t_node	*start;
	int		i;
	int		j;

	i = 0;
	check_double_links(node);
	while (i < data->start->n_links)
	{
		j = 0;
		while (j < data->start->n_links)
			data->start->links[j++]->ihbt = 1;
		start = data->start->links[i];
		start->start = 0x1;
		if (!(search_path(start)))
		{
			cut_and_reset(data->start, i, NULL, 0);
			i = 0;
		}
		cut_and_reset(NULL, 0, node, 1);
		start->start = 0;
		i++;
	}
	if (!data->start->n_links)
		ft_error("Start no unido con end\n");
	data->end->start = 0x1;
	data->end->end = 0;
	data->start->start = 0;
	data->start->end = 0x1;
	i = 0;
	while (i < data->end->n_links)
	{
		j = 0;
		while (j < data->end->n_links)
			data->end->links[j++]->ihbt = 1;
		start = data->end->links[i];
		start->start = 0x1;
		if (!(search_path(start)))
		{
			cut_and_reset(data->end, i, NULL, 0);
			i = 0;
		}
		cut_and_reset(NULL, 0, node, 1);
		start->start = 0;
		i++;
	}
	data->end->start = 0;
	data->end->end = 0x1;
	data->start->start = 0x1;
	data->start->end = 0;
}
