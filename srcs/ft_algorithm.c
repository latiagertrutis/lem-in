/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:35:46 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/23 14:34:13 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void		prepare_graf(t_node *node, t_map *conj, int cuant)
{
	t_path	*tmp;

	while(cuant--)
		conj = conj->next;
	while (node)
	{
		tmp = conj->path;
		while (tmp)
		{
			if (!(node->end) && node->id == tmp->node->id)
			{
				node->ihbt = 2;
				break ;
			}
			else
				tmp = tmp->next;
		}
		if (!tmp)
			node->ihbt = 0;
		node = node->next;
	}
}

static int check_compatible(t_map **conj, int max)
{
	int	i;
	int	j;
	t_path *tmp;
	t_path *tmp2;

	i = 0;
	j = 0;
	while (j < max)
	{
		i = j + 1;
		tmp = conj[j]->path;
		while (i < max)
		{
			tmp2 = conj[i]->path;
			while (tmp)
			{
				while (tmp2)
				{
					if (tmp->node->id == tmp2->node->id)
						return (0);
					tmp2 = tmp2->next;
				}
				tmp = tmp->next;
			}
			i++;
		}
		j++;
	}
	return (1);
}

static void	destroy_path(t_map *conj)
{
	while (conj)
	{
		while (conj->tail)
		{
			if (conj->tail->prev)
			{
				conj->tail = conj->tail->prev;
				free(conj->tail->next);
			}
			else
			{
				free(conj->tail);
				break ;
			}
		}
		if (conj->next)
		{
			conj = conj->next;
			free(conj->prev);
		}
		else
		{
			free(conj);
			break ;
		}
	}
}

t_map	**ft_algorithm(t_data *data, t_node *node)
{
	t_map	**conj;
	int		i;
	int		j;
	int		tmp;
	int		*cuant;
	int		max;

	max = ft_min(data->start->n_links, data->end->n_links);
	conj = (t_map **)ft_memalloc(sizeof(t_map *) * (max + 1));
	cuant = (int *)ft_memalloc(sizeof(int) * (data->start->n_links + 1));
	cuant[data->start->n_links] = -1;
	conj[max] = NULL;
	tmp = 0;
	i = 0;
	j = 1;
	while (i < data->start->n_links && i >= 0 && (max - j) >= 0)
	{
		data->start->ihbt = 1;
		data->start->links[i]->start = 0x1;
		if ((conj[max - j] = ft_search_paths2(data->start->links[i], cuant + i, tmp)))
		{
			ft_printf("Tengo %i caminos\n", cuant[i]);
			data->start->links[i]->start = 0;
			if (!(max - j) && check_compatible(conj, max))
				return (conj);
			prepare_graf(node, conj[max - j], cuant[i] - 1);
			i++;
			j++;
		}
		else
		{
			ft_printf("No hay caminos\n");
			j--;
			i--;
			tmp = conj[max - j]->len;
			destroy_path(conj[max - j]);
			exit(1);
		}
	}
	return (conj);
}
