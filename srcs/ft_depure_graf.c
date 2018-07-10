/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_depure_graf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:23:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/10 03:48:24 by jagarcia         ###   ########.fr       */
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

static void		bfs_core(t_path **bfs, int *len, int i[2])
{
	*bfs = !((*len + 1) % ALGORITHM_BUFF) ? ft_realoj(*bfs, *len) : *bfs;
	(*bfs)[++*len].node = (*bfs)[i[0]].node->links[i[1]];
	(*bfs)[*len].prev = *bfs + i[0];
}

static int		search_path(t_node *start, int len, t_data *data, t_map **map)
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
				bfs_core(&bfs, &len, i);
				if (bfs[len].node->end)
				{
					if (data->short_path)
						*map = ft_make_path(bfs, 1, len);
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

static int		core(t_node *core, t_node *node, t_data *data, t_map **map)
{
	int		i[2];
	t_node	*tmp;

	i[0] = -1;
	while (++i[0] < core->n_links)
	{
		i[1] = 0;
		while (i[1] < core->n_links)
			core->links[i[1]++]->ihbt = 1;
		tmp = core->links[i[0]];
		tmp->start = 0x1;
		if (!(search_path(tmp, 0, data, map)))
		{
			ft_cut_and_reset(core, i[0], NULL, 0);
			i[0] = -1;
		}
		else if (*map)
			return (1);
		ft_cut_and_reset(NULL, 0, node, 1);
		tmp->start = 0;
	}
	if (!core->n_links)
		ft_line_error(-1, "Start no unido con end\n");
	return (0);
}

t_map			*ft_depure_graf(t_data *data, t_node *node)
{
	t_map *map;

	map = NULL;
	check_double_links(node);
	if ((core(data->start, node, data, &map)))
		return (map);
	else
	{
		data->end->start = 0x1;
		data->end->end = 0;
		data->start->start = 0;
		data->start->end = 0x1;
		core(data->end, node, data, &map);
		data->end->start = 0;
		data->end->end = 0x1;
		data->start->start = 0x1;
		data->start->end = 0;
	}
	return (NULL);
}
