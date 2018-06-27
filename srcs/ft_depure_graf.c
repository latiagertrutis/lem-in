/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_paths2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:23:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/27 16:22:57 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/* static t_path	*realoj(t_path *src, int len) */
/* { */
/* 	t_path *new; */

/* 	if (!(new = (t_path *)ft_memalloc(sizeof(t_path) * (len + 1001)))) */
/* 		ft_error("Error malloc en realoj\n"); */
/* 	while (len) */
/* 	{ */
/* 		new[len] = src[len]; */
/* 		len--; */
/* 	} */
/* 	return (new); */
/* } */

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
	ft_printf("voy a comprobar %s\n", start->name);
	while (++i <= len)
	{
		j = -1;
		while(++j < bfs[i].node->n_links)
		{
			if (!bfs[i].node->links[j]->ihbt && !bfs[i].node->links[j]->start)
			{
//				ft_printf("Estoy en %s y voy a anyadir %s\n", bfs[i].node->name, bfs[i].node->links[j]->name);
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

static void	cut_and_reset(t_node *true_start, int pos, t_node *node, int reset)
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

void	ft_depure_graf(t_data *data, t_node *node)
{
	t_node	*start;
	int		i;

	i = 0;
	while (i < data->start->n_links)
	{
		start = data->start->links[i];
		start->start = 0x1;
		start->ihbt = 1;
		if (!(search_path(start)))
		{
//			ft_printf("Voy a romper la union %s\n", start->name);
			cut_and_reset(data->start, i, NULL, 0);
			i = 0;
		}
		cut_and_reset(NULL, 0, node, 1);
		start->start = 0;
		i++;
	}
	if (!data->start->n_links)
		ft_error("Start no unido con end\n");
}
