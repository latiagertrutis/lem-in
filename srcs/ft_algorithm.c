/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:35:46 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/24 20:23:59 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int		compare_path(const t_node *node, t_path *path)
{
	while (path)
	{
		if (path->node == node)
			return (1);
		path = path->next;
	}
	return (0);
}

static void		prepare_graf(t_node *node, t_path *path, int mode)
{
	while (node)
	{
		if ((node->ihbt && !mode && (node->ihbt != 2 || compare_path(node, path))) || node->end)
			node->ihbt = 0;
		else if (mode && node->ihbt != 2 && compare_path(node, path))
			node->ihbt = 2;
		else if (node->ihbt != 2)
			node->ihbt = 0;
		node = node->next;
	}
}
static void	destroy_path(t_map *map, const int n)
{
	int		i;
	t_path	*aux;

	i = 0;
	while (i < n && map)
	{
		map = map->next;
		i++;
	}
	while (map->path)
	{
		aux = map->path->next;
		free(map->path);
		map->path = aux;
	}
	if (!n)
		free(map);
}

static void	reset_graf(t_node *node, t_node *start, int *cuant)
{
	int	i;

	i = 0;
	while (node)
	{
		node->ihbt = 0;
		node = node->next;
	}
	while (i < start->n_links)
		cuant[i++] = 0;
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
	j = max;
	ft_printf("Debo tener %i conjuntos\n", max);
	while (i < data->start->n_links && i >= 0 && j > 0)
	{
		data->start->ihbt = 1;
		data->start->links[i]->start = 0x1;
		if (!(conj[max - j] = ft_search_paths2(data->start->links[i], cuant + i, tmp)))
		{
			ft_printf("No he encontrado paths\n");
			if (!i)
				ft_error("Start y Exit no unidos\n");
			i--;
			ft_error("No paths\n");
			prepare_graf(node, conj[max - j][cuant[i]].path, 0);
			destroy_path(conj[max - j], cuant[i]);
		}
		ft_printf("Tengo %i caminos\n", cuant[i]);
		data->start->links[i]->start = 0;
		if (!cuant[i])
		{
			tmp = conj[max - j]->len;
			destroy_path(conj[max - j], 0);
		}
		else if (conj[max - j] && i + 1 == max - j + 1)
		{
			ft_printf("he completado el conjunto %i\n", max - j);
			reset_graf(node, data->start, cuant);
			i = 0;
			j--;
		}
		else
		{
			prepare_graf(node, conj[max - j][--cuant[i]].path, 1);
			i++;
			conj[max - j] = conj[max - j]->next;
		}
	}
	return (conj);
}
