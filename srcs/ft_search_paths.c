/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 04:12:39 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/22 11:14:20 by jagarcia         ###   ########.fr       */
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

static void	path_lector(t_path *path)
{	
	while(path)
	{
		ft_printf("%s - ", path->node->name);
		path = path->next;
	}
}

static int	check_paths(t_map **map, int pos)
{

	if (!(*map)->path->node->end && !((*map)->path->node->start && !(*map)->path->prev && (*map)->len > 1))
		return (pos);
	else
	{
		while ((*map)->path->node->end)
		{
//			ft_printf("El path %i esta completo\n",pos);
			(*map)->path = (*map)->head;
//			ft_printf("Path %i", pos);
//			path_lector((*map)->path);
//			ft_putchar('\n');
			if (!(*map)->next)
				return (-1);
			(*map) = (*map)->next;
			pos++;
		}
		(*map)->path = (*map)->head;
		while ((*map)->path->next)
		{
			(*map)->path->node->ihbt = pos;
			(*map)->path = (*map)->path->next;
		}
		(*map)->path->node->ihbt = pos;
		
		return (pos);
	}
}

t_map		*ft_new_map(t_path *path, t_map *prev)
{
	t_map	*map;
	
	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		ft_error("Error malloc ft_search_paths\n");
	map->path = path;
	map->prev = prev;
	map->len = 1;
	map->head = path;
	return (map);
}

static void	copy_paths(t_map *map, int pos, int *len, t_map **end_map)
{
	t_map	*tmp_map;
	t_path	*tmp_path;
	int		i;
	int		n_links;

	n_links = map->path->node->n_links;
	tmp_map = map;
	tmp_map = *end_map;
	i = 0;
	while (i < n_links && map->path->node->links[i]->ihbt == pos)
		i++;
	if (i > n_links - 1)
	{
		*len = -1;
		return ;
	}
//	ft_printf("Estoy en el nodo %s y voy a anyadirle el nodo %s que tiene i = %i\n", map->path->node->name, map->path->node->links[i]->name, i);
	tmp_path = ft_new_path(map->path->node->links[i], map->path, &(map->len));
	map->path->node->links[i]->ihbt = pos;
	i++;
	while (n_links - i > 0)
	{
		while (i <= n_links - 1 && map->path->node->links[i]->ihbt == pos)
			i++;
		if (i > n_links - 1)
			break ;
		map->path = map->head;
		tmp_map->next = ft_new_map(ft_new_path(map->path->node, NULL, 0), tmp_map);
		tmp_map = tmp_map->next;
		while (map->path->next)
		{
//			ft_printf("Voy a copiar el nodo %s delante de %s\n",map->path->next->node->name, tmp_map->path->node->name);
			map->path = map->path->next;
			tmp_map->path->next = ft_new_path(map->path->node, tmp_map->path, &(tmp_map->len));
			tmp_map->path = tmp_map->path->next;
		}
//		ft_printf("He copiado el nodo %s y voy a anyadirle el nodo %s que tiene i = %i\n", tmp_map->path->node->name, map->path->node->links[i]->name, i);
		tmp_map->path->next = ft_new_path(map->path->node->links[i], tmp_map->path, &(tmp_map->len));
		tmp_map->path = tmp_map->path->next;
		tmp_map->path->node->ihbt = pos;
		i++;
	}
	*end_map = tmp_map;
	map->path->next = tmp_path;
	map->path = map->path->next;
}

static int	destroy_path(t_map **map, int pos, t_map **map_head)
{
	t_map	*tmp;
	t_path	*tmp_path;

	while ((*map)->path)
	{
		tmp_path = (*map)->path;
		(*map)->path = (*map)->path->prev;
		free(tmp_path);
	}
	tmp = *map;
//	if (!(*map)->path)
//		ft_putstr("Es nulo, bien\n");
	
	if ((*map)->next && (*map)->prev)
	{
//		ft_printf("El siguiente es %s\n", (*map)->next->path->node->name);
//		ft_printf("El anterior es %s\n",(*map)->prev->path->node->name);
		(*map)->next->prev = (*map)->prev;
		(*map)->prev->next = (*map)->next;
		*map = (*map)->next;
	}
	else if (!(*map)->next && (*map)->prev)
	{
//		ft_printf("El anterior es %s\n",(*map)->prev->path->node->name);
		(*map)->prev->next = NULL;
		*map = (*map)->prev;
	}
	else if (!(*map)->prev && (*map)->next)
	{
//		ft_printf("El siguiente es %s\n", (*map)->next->path->node->name);
		(*map)->next->prev = NULL;
		*map = (*map)->next;
		*map_head = *map;
	}
	free(tmp);
//	ft_printf("Ahora estoy en el nodo %s\n", (*map)->path->node->name);
	pos = pos + 1;
	(*map)->path = (*map)->head;
	while ((*map)->path->next)
	{
		(*map)->path->node->ihbt = pos;
		(*map)->path = (*map)->path->next;
	}
	(*map)->path->node->ihbt = pos;
	return (pos);
}

t_map	*ft_search_paths(t_node *graf)
{
	t_map	*head_map;
	t_map	*end_map;
	t_map	*tmp_map;
	int		pos;

	pos = 1;
	head_map = ft_new_map(ft_new_path(graf, NULL, 0), NULL);
	tmp_map = head_map;
	end_map = head_map;
	head_map->path->node->ihbt = 1;
	while ((pos = check_paths(&tmp_map, pos)) >= 0)
	{
		if (tmp_map->len < 0)
		{
//			ft_printf("DELETING\n");
//			ft_printf("Estoy en el nodo %s y la longitud del path por ahora es %i\n", tmp_map->path->node->name, tmp_map->len);
			pos = destroy_path(&tmp_map, pos, &head_map);
//			ft_printf("DELETED\n");
		}
		else
		{
//			ft_printf("COPYING\n");
//			ft_printf("Estoy en el nodo %s que tiene %i links\n", tmp_map->path->node->name, tmp_map->path->node->n_links);
			copy_paths(tmp_map, pos, &(tmp_map->len), &(end_map));
//			ft_printf("COPIED\n");
//			ft_printf("Ahora estoy en el nodo %s\n", tmp_map->path->node->name);
		}
//		ft_map_lector(head_map, NULL);
	}
	return (head_map);
}
