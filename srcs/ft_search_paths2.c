/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_paths2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:23:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/22 16:52:17 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_path	*ft_new_path2(t_node *node, t_path *next, int *len)
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

t_map	*ft_search_paths2(t_data *data)
{
	t_path	*bfs;
	t_path	*tmp;
	t_node	*graf;
	t_map	*conj;
	int		max_paths;
	int		len;
	int		i;
	int		j;
	int		end;

	graf = data->start;
	max_paths = graf->n_links < data->end->n_links ? graf->n_links : data->end->n_links;
	if (!(bfs = (t_path *)ft_memalloc(1000 * sizeof(t_path))))
		ft_error("Error malloc ft_search_paths2\n");
	bfs[0].node = graf;
	bfs[0].node->ihbt = 1;
	bfs[0].prev = NULL;
	i = 0;
	j = 0;
	len = 0;
	end = 0;
	while (!bfs[i].node->end)
	{
		ft_printf("Estoy en el nodo %s\n", bfs[i].node->name);
		j = 0;
		while(j < bfs[i].node->n_links)
		{
			if (!bfs[i].node->links[j]->ihbt)
			{
				ft_printf("Voy a anyadir el nodo %s\n",bfs[i].node->links[j]->name);
				bfs[len++ + 1].node = bfs[i].node->links[j];
				bfs[len].prev = bfs + i;
				if (bfs[len].node->end)
					end++;
				else
					bfs[len].node->ihbt = 1;
			}
			j++;
		}
		i++;
	}
	ft_printf("Tengo %i caminos\n", end);
	if (!(conj = (t_map *)ft_memalloc(sizeof(t_map) * (end + 1))))
		ft_error("Error malloc ft_search_paths2\n");
	conj[end].path = NULL;
	i = 0;
	j = 0;
	while (end)
	{
		if (bfs[len - i].node->end)
		{
			ft_printf("He encontrado un end\n");
			conj[j].path = ft_new_path2(bfs[len - i].node, NULL, 0);
			tmp = bfs + len - i;
			end--;
			while (!conj[j].path->node->start)
			{
				ft_printf("Estoy en %s\n", conj[j].path->node->name);
				conj[j].path = conj[j].path->prev;
				conj[j].path = ft_new_path2(conj[j].path->prev->node, conj[j].path, 0);
				ft_printf("Estoy en %s\n", conj[j].path->node->name);
			}
			j++;
		}
		i++;
	}
	return (conj);
}
