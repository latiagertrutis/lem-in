/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:35:46 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/26 18:07:31 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	ft_algorithm_core(t_map **conj, int *cuant, t_data *data, t_node *node)
{
	int		i[2];
	int		tmp;
	int		max;
	t_map	*prev;

	max = ft_min(data->start->n_links, data->end->n_links);
	i[0] = 0;
	i[1] = max;
	prev = NULL;
	while (i[0] < data->start->n_links && i[0] >= 0 && i[1] > 0)
	{
		data->start->ihbt = 1;
		data->start->links[i[0]]->start = 0x1;
		if (!(conj[max - i[1]] = ft_search_paths2(data->start->links[i[0]], cuant + i[0], tmp)))
			ft_no_path(conj + max - i[1], &prev, node, cuant[--i[0]]);
		data->start->links[i[0]]->start = 0;
		ft_assign_prev(conj[max - i[1]], prev);
		tmp = ft_no_more_paths(conj[max - i[1]], cuant + i[0]);
		if (cuant[i[0]] && conj[max - i[1]] && i[0] + 1 == max - i[1] + 1)
			ft_finish_conj(conj + max - i[1]--, node, cuant, i[0]);
		else if (cuant[i[0]])
			tmp = ft_prepare_next_path(conj + max - i[1], node, --cuant[i[0]++], &prev);
	}
}

t_map	**ft_algorithm(t_data *data, t_node *node)
{
	t_map	**conj;
	int		*cuant;
	int		max;

	max = ft_min(data->start->n_links, data->end->n_links);
	if (!(conj = (t_map **)ft_memalloc(sizeof(t_map *) * (max + 1))))
		ft_error("Error Malloc algorithm\n");
	if (!(cuant = (int *)ft_memalloc(sizeof(int) * (data->start->n_links + 1))))
		ft_error("Error Malloc algorithm\n");
	cuant[data->start->n_links] = -1;
	ft_algorithm_core(conj, cuant, data, node);
	return (conj);
}
