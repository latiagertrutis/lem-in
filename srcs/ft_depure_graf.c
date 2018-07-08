/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_depure_graf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:23:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/09 01:36:24 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_path	*ini_bfs(int *i, int *len, t_node *start)
{
	t_path	*bfs;
	int		size;

	size = ALGORITHM_BUFF;
	if (!(bfs = (t_path *)ft_memalloc(ALGORITHM_BUFF * sizeof(t_path))))
		ft_error("Error malloc ft_search_paths2\n");
	bfs[0].node = start;
	bfs[0].node->ihbt = 1;
	bfs[0].prev = NULL;
	*i = -1;
	*len = 0;
	return (bfs);
}

static int		search_path(t_node *start, int len)
{
	t_path	*bfs;
	int		i[2];

	bfs = ini_bfs(&i[0], &len, start);
	while (++i[0] <= len && (i[1] = -1))
	{
		while (++i[1] < bfs[i[0]].node->n_links)
		{
			if (!bfs[i[0]].node->links[i[1]]->ihbt &&
					!bfs[i[0]].node->links[i[1]]->start)
			{
				bfs = !((len + 1) % ALGORITHM_BUFF) ? ft_realoj(bfs, len) : bfs;
				bfs[++len].node = bfs[i[0]].node->links[i[1]];
				bfs[len].prev = bfs + i[0];
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
						|| !node->links[i]->end) && (!node->end ||
							!node->links[i]->end)))
					ft_cut_and_reset(node, i, NULL, 0);
			}
			i++;
		}
		node = node->next;
	}
}

static void		core(t_node *core, t_node *node)
{
	int		i;
	int		j;
	t_node	*tmp;
	int		len;

	len = 0;
	i = 0;
	while (i < core->n_links)
	{
		j = 0;
		while (j < core->n_links)
			core->links[j++]->ihbt = 1;
		tmp = core->links[i];
		tmp->start = 0x1;
		if (!(search_path(tmp, len)))
		{
			ft_cut_and_reset(core, i, NULL, 0);
			i = 0;
		}
		ft_cut_and_reset(NULL, 0, node, 1);
		tmp->start = 0;
		i++;
	}
	if (!core->n_links)
		ft_line_error(-1, "Start no unido con end\n");
}

void			ft_depure_graf(t_data *data, t_node *node)
{
	check_double_links(node);
	core(data->start, node);
	data->end->start = 0x1;
	data->end->end = 0;
	data->start->start = 0;
	data->start->end = 0x1;
	core(data->end, node);
	data->end->start = 0;
	data->end->end = 0x1;
	data->start->start = 0x1;
	data->start->end = 0;
}
