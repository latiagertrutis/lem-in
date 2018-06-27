/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:35:46 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/27 16:57:46 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_map	**ini_algorithm(int i[2], t_map *tail_head[2], int *tmp, int max)
{
	t_map	**conj;
	
	conj = (t_map **)ft_memalloc(sizeof(t_map *) * (max + 1));
	*tmp = 0;
	i[0] = 0;
	i[1] = max;
	tail_head[1] = NULL;
	tail_head[0] = NULL;
	return (conj);
}

t_map	**ft_algorithm(t_data *data, t_node *node, int max)
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
		data->start->ihbt = 1;
		data->start->links[i[0]]->start = 0x1;
		if (!(conj[max - i[1]] = ft_search_paths(data->start->links[i[0]], &cuant, &tmp)))
		{
			ft_printf("No he encontrado camino voy a destruit el camino\n");
			i[0]--;
			tmp = ft_no_path(node, tail_head, &cuant, conj + max - i[1]);
		}
		data->start->links[i[0]]->start = 0;
		ft_printf("Tengo %i caminos y son:\n", cuant);
		if (!tail_head[0])
			ft_map_lector(conj[max - i[1]], NULL);
		else
			ft_map_lector(tail_head[0], NULL);
		if (conj[max - i[1]] && i[0] + 1 == max - i[1] + 1)
		{
			ft_printf("He acabado un conjunto y es:\n");
			i[0] = ft_finish_conjunt(tail_head, conj + max - i[1]--, node, &cuant);
		}
		else if (!tmp)
		{
			ft_printf("Voy a preparar el camino\n");
			i[0] += ft_prepare_next(tail_head, conj + max - i[1], cuant, node);
		}
	}
	return (conj);
}
