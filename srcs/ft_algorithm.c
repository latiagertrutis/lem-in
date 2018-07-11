/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:35:46 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/11 03:57:45 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_map	**ini_algorithm(int i[2], t_map *tail_head[2],
									int *tmp, int max)
{
	t_map	**conj;

	if (!(conj = (t_map **)ft_memalloc(sizeof(t_map *) * (max + 1))))
		ft_error("Error malloc ini_algorithm\n");
	*tmp = 0;
	i[0] = 0;
	i[1] = max;
	tail_head[1] = NULL;
	tail_head[0] = NULL;
	return (conj);
}

t_map			**ft_algorithm(t_data *data, t_node *node, int max)
{
	t_map	**conj;
	t_map	*(tail_head[2]);
	int		i[2];
	int		tmp;
	int		cuant;

	conj = ini_algorithm(i, tail_head, &tmp, max);
	cuant = 0;
	while (i[0] < data->start->n_links && i[0] >= 0 && i[1] > 0)
	{
		if (!(conj[max - i[1]] = ft_search_paths(data->start, &cuant, &tmp)))
		{
			i[0]--;
			tmp = ft_no_path(node, tail_head, &cuant, conj + max - i[1]);
		}
		if (conj[max - i[1]] && i[0] + 1 == max - i[1] + 1)
			i[0] = ft_finish_conjunt(tail_head, conj + max - i[1]--,
										node, &cuant);
		else if (!tmp)
			i[0] += ft_prepare_next(tail_head, conj + max - i[1], cuant, node);
	}
	return (conj);
}
