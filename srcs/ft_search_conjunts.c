/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 04:12:39 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/17 08:05:59 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_path	*ft_new_path(t_node *node, t_path *prev, int *len)
{
	t_path	*path;
	
	if (!(path = (t_path *)ft_memalloc(sizeof(t_path))))
		ft_error("Error malloc ft_new_path\n");
	path->next = NULL;
	path->prev = prev;
	path->node = node;
	if (len)
		(*len)++;
	return (path);
}

static int	check_paths(t_map *map)
{
	int	pos;
	t_path	*tmp_path;

	pos = 0;
	while (map)
	{
		tmp_path = map->path;
		if (!tmp_path->node->end)
			return (pos);
		map = map->next;
		pos++;
	}
	return (-1);
}

t_map		*ft_new_map(t_path *path, t_map *prev)
{
	t_map	*map;
	
	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		ft_error("Error malloc ft_search_paths\n");
	map->path = path;
	map->prev = prev;
	map->len = 1;
	return (map);
}

static void	copy_paths(t_map *map, int n_links)
{
	t_path	*tmp;
	t_path	*tmp2;
	
	tmp = map->path;
	while (n_links > 1)
	{
		while(tmp->prev)
			tmp = tmp->prev;
		map->next = ft_new_map(ft_new_path(tmp->node, NULL, 0), map);
		map = map->next;
		tmp2 = map->path;
		while (tmp)
		{
			tmp = tmp->next;
			tmp2->next = ft_new_path(tmp->node, tmp2, &(map->len));
			tmp2 = tmp2->next;
		}
	}
}

static void	destroy_path(t_map *map)
{
	t_map *tmp;

	while (map->path)
	{
		free(map->path);
		map->path = map->path->prev;
	}
	tmp = map;
	map->prev->next = map->next;
	map->next->prev = map->prev;
	free(tmp);
}

t_map	*ft_search_paths(t_node *graf)
{
	t_map	*map;
	int		pos;
	t_map	*tmp_map;

	map = ft_new_map(ft_new_path(graf, NULL, 0), NULL);
	tmp_map = map;
	while ((pos = check_paths(map)) >= 0)
	{
		while (pos--)
			tmp_map = tmp_map->next;
		if (tmp_map->path->node->n_links > 1)
			copy_paths(tmp_map, tmp_map->path->node->n_links);
		if (!tmp_map->path->node->ihbt || (tmp_map->path->node->start && tmp_map->len > 1))
			destroy_path(tmp_map);
		else
		{
			tmp_map->path->next = ft_new_path(tmp_map->path->node->links + tmp_map->path->node->ihbt--, tmp_map->path, &(tmp_map->len));
			tmp_map->path = tmp_map->path->next;
		}
	}
	return (map);
}
