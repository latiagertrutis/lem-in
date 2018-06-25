/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 21:52:24 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/25 23:40:49 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int		send_ants(int dim, t_map *conj, double **mat, int *ant)
{
	int i;
	int centi;

	i = 0;
	centi = 0;
	while (conj)
	{
		if (mat[i][dim - 1] > 0.9)
		{
			ft_printf("L%d-%s", *ant, conj->path->node->name);
			mat[i][dim - 1]--;
			(*ant)++;
			conj->path->node->ants = *ant;
			centi = 1;
		}
		conj = conj->next;
	}
	return (centi);
}

static void		lagging_ants(t_data *data, int *ant, t_map *conj)
{
	int i;

	i = 0;
	while (conj && *ant != data->n_ants)
	{
		ft_printf("L%d-%s", *ant, conj->path->node->name);
		(*ant)++;
		conj->path->node->ants = *ant;
		conj = conj->next;
	}
}

static int		move_ants(t_data *data, t_map *conj)
{
	t_path *path;

	while (conj)
	{
		path = conj->tail;
		while (path)
		{
			if (path->node->ants)
			{
				ft_printf("L%d-%s", path->node->ants, path->next->node->name);
				if (path->next->node->end)
				{
					path->next->node->ants++;
					if (path->node->ants == data->n_ants)
						return (0);
				}
				else
					path->next->node->ants = path->node->ants;
				path->node->ants = 0;
			}
			path = path->prev;
		}
		conj = conj->next;
	}
	return(1);
}

void			ft_solution(t_data *data, t_map *conj, double **mat, int dim)
{
	int ant;

	ant = 1;
	while (ant != data->n_ants)
	{
		move_ants(data, conj);
		if (!send_ants(dim, conj, mat, &ant))
			lagging_ants(data, &ant, conj);
	}
	while (move_ants(data, conj));
}
