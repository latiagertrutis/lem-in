/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_funcs2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:05:21 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/26 18:12:52 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"


int		ft_compare_path(const t_node *node, t_path *path)
{
	while (path)
	{
		if (path->node == node)
			return (1);
		path = path->next;
	}
	return (0);
}

void		ft_prepare_graf(t_node *node, t_map *map, int pos, int mode)
{
	t_path *path;

	while (pos--)
		map = map->next;
	path = map->path;
	map->len *= -1;
	while (node)
	{
		if ((node->ihbt && !mode && (node->ihbt != -1 ||
				ft_compare_path(node, path))) || node->end)
			node->ihbt = 0;
		else if (mode && node->ihbt != -1 && ft_compare_path(node, path))
			node->ihbt = -1;
		else if (node->ihbt != -1)
			node->ihbt = 0;
		node = node->next;
	}
}
void	ft_destroy_path(t_map *map, const int n)
{
	int		i;
	t_path	*aux;
	t_map	*prev;
	t_map	*next;

	i = 0;
	while (i++ < n - 1 && map)
		map = map->next;
	while (map->path)
	{
		aux = map->path->next;
		free(map->path);
		map->path = aux;
	}
	if ((prev = map->prev) && (next = map->next))
	{
		map->prev->next = map->next;
		map->next->prev = map->prev;
	}
	else if ((prev = map->prev) && !(next = map->next))
		map->prev->next = map->next;
	else if (!(prev = map->prev) && (next = map->next))
		map->next->prev = map->prev;
	free(map);
}

void	ft_reset_graf(t_node *node, int *cuant)
{
	int	i;

	i = 0;
	while (node)
	{
		node->ihbt = 0;
		node = node->next;
	}
	while (cuant[i] > 0)
		cuant[i++] = 0;
}
