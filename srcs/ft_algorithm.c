/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:35:46 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/25 12:34:37 by jagarcia         ###   ########.fr       */
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
		if ((node->ihbt && !mode && (node->ihbt != -1 || compare_path(node, path))) || node->end)
			node->ihbt = 0;
		else if (mode && node->ihbt != -1 && compare_path(node, path))
			node->ihbt = -1;
		else if (node->ihbt != -1)
			node->ihbt = 0;
		node = node->next;
	}
}
static void	destroy_path(t_map *map, const int n)
{
	int		i;
	t_path	*aux;

	i = 0;
	while (i < n - 1 && map)
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
	t_map	*prev;
	t_map	*head;
	int		i;
	int		j;
	int		tmp;
	int		*cuant;
	int		max;

	prev = NULL;
	if (!(max = ft_min(data->start->n_links, data->end->n_links)))
		ft_error("Start y Exit no unidos\n");
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
		ft_printf("El proximo camino debera ser menor de %i\n", tmp);
		if (!(conj[max - j] = ft_search_paths2(data->start->links[i], cuant + i, tmp)))
		{
			ft_printf("No he encontrado paths\n");
			if (!i)
				ft_error("Start y Exit no unidos\n");
			i--;
			conj[max - j] = prev;
			prev = NULL;
			prepare_graf(node, conj[max - j][cuant[i]].path, 0);
			ft_printf("Borro el camino %i\n", cuant[i]);
			destroy_path(conj[max - j], cuant[i] + 1);
			for(t_node *tmp = node; tmp; tmp = tmp->next)
				ft_printf("El nodo %s esta a %i\n", tmp->name, tmp->ihbt);
//			ft_error("No paths\n");
		}
		ft_printf("Tengo %i caminos\n", cuant[i]);
		data->start->links[i]->start = 0;
		if (!cuant[i])
		{
			ft_printf("Ya no me quedan caminos y el anterior media %i\n", conj[max - j]->len);
			tmp = conj[max - j]->len;
			destroy_path(conj[max - j], 0);
			prev = NULL;
		}
		else if (conj[max - j] && i + 1 == max - j + 1)
		{
			ft_printf("He completado el conjunto %i\n", max - j);
			if (prev)
			{
				prev->next = conj[max - j];
				conj[max - j]->prev = prev;
			}
			while (conj[max - j]->prev)
			{
				ft_printf("Rebobino\n");
				conj[max - j] = conj[max - j]->prev;
			}
			ft_putstr("[[[[\n");
			ft_map_lector(conj[max - j], NULL);
			ft_putstr("]]]]\n");
			if (!conj[max - j]->next)
				ft_putstr("No hay next\n");
			prev = NULL;
			reset_graf(node, data->start, cuant);
			i = 0;
			j--;
		}
		else
		{
			ft_printf("Preparo siguiente camino\n");
			tmp = 0;
			prepare_graf(node, conj[max - j][--cuant[i]].path, 1);
			i++;
			if (prev)
			{
				prev->next = conj[max - j];
				ft_printf("Voy a poner el nodo %s detras\n", prev->path->node->name);
				conj[max - j]->prev = prev;
			}
			prev = conj[max - j];
			conj[max - j] = conj[max - j]->next;
//			conj[max - j]->prev = prev;
		}
	}
	return (conj);
}
