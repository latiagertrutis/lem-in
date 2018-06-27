/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 21:52:24 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/27 17:37:53 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static char		*assign_color(int ant)
{
	char	*str;
	char	*aux;
	int		len;

	aux = ft_itoa(ant % 256);
	len = ft_strlen(aux);
	str = ft_strjoin("{C:", aux);
	free(aux);
	aux = str;
	str = ft_strjoin(aux, "}");
	free(aux);
	return (str);
}

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
			(*ant)++;
			ft_printf("%sL%d-%s ", assign_color(*ant),
									*ant, conj->path->next->node->name);
			mat[i][dim - 1]--;
			conj->path->next->node->ants = *ant;
			centi = 1;
		}
		conj = conj->next;
		i++;
	}
	return (centi);
}

static void		lagging_ants(t_data *data, int *ant, t_map *conj)
{
	int i;

	i = 0;
	while (conj && *ant != data->n_ants)
	{
		(*ant)++;
		ft_printf("%sL%d-%s ", assign_color(*ant),
								*ant, conj->path->node->name);
		conj->path->node->ants = *ant;
		conj = conj->next;
	}
}

static int		move_ants(t_data *data, t_map *conj)
{
	t_path *path;

	while (conj)
	{
		path = conj->tail->prev;
		while (path && !path->node->start)
		{
			if (path->node->ants)
			{
				ft_printf("%sL%d-%s ", assign_color(path->node->ants),
							path->node->ants, path->next->node->name);
				if (path->next->node->end)
				{
					if (++(path->next->node->ants) >= data->n_ants)
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
	return (1);
}

void			ft_solution(t_data *data, t_map *conj, double **mat, int dim)
{
	int ant;

	ant = 0;
	while (ant < data->n_ants)
	{
		move_ants(data, conj);
		if (!send_ants(dim, conj, mat, &ant))
			lagging_ants(data, &ant, conj);
		ft_putstr("\n");
	}
	while (move_ants(data, conj))
		ft_putstr("\n");
	ft_printf("{eoc}\n");
}
