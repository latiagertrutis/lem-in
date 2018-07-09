/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 21:52:24 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/09 03:40:01 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void		assign_color(int ant, char *name)
{
	char	*str;
	char	*aux;
	int		len;

	(void)name;
	if (!(ant % 15))
		aux = ft_itoa(15);
	else
		aux = ft_itoa((ant % 15));
	len = ft_strlen(aux);
	str = ft_strjoin("{C:", aux);
	free(aux);
	aux = str;
	str = ft_strjoin(aux, "}");
	free(aux);
	ft_printf("%sL%d-%s ", str, ant, name);
	free(str);
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
			assign_color(*ant, conj->path->next->node->name);
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
		assign_color(*ant, conj->path->next->node->name);
		conj->path->next->node->ants = *ant;
		conj = conj->next;
	}
}

static int		move_ants(t_data *data, t_map *conj)
{
	t_path *path;

	while (conj)
	{
		path = conj->tail->prev;
		while (path)
		{
			if (path->node->ants)
			{
				assign_color(path->node->ants, path->next->node->name);
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
	if (conj->path->next->node->end)
	{
		while (ant < data->n_ants)
			assign_color(ant++, conj->path->next->node->name);
		ft_putstr("\033[0m\n");
		return ;
	}
	while (ant < data->n_ants)
	{
		move_ants(data, conj);
		if (!send_ants(dim, conj, mat, &ant))
			lagging_ants(data, &ant, conj);
		ft_putstr("\n");
	}
	while (move_ants(data, conj))
		ft_putstr("\n");
	ft_putstr("\033[0m\n");
}
