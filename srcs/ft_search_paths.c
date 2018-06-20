/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 04:12:39 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/20 06:54:39 by jagarcia         ###   ########.fr       */
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

static int	check_paths(t_map **map, int pos)
{

	if (!(*map)->path->node->end && !((*map)->path->node->start && !(*map)->path->prev && (*map)->len > 1))
		return (pos);
	else
	{
		ft_printf("El path %i esta completo\n",pos);
		if (!(*map)->next)
		{
			(*map)->path = (*map)->head;
			return (-1);
		}
		(*map)->path = (*map)->head;			
		(*map) = (*map)->next;
		pos++;
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

static void	copy_paths(t_map *map, int n_links, int pos, int *len)
{
	t_map	*tmp_map;
	t_path	*tmp_path;
	int		i;

	tmp_map = map;
	while (tmp_map->next)
		tmp_map = tmp_map->next;
	i = 0;
	while (i < n_links && map->path->node->links[i]->ihbt == pos)
	{
		ft_printf("El nodo %s tiene pos=%i\n", map->path->node->links[i]->name, map->path->node->links[i]->ihbt);
		i++;
	}
	if (i > n_links - 1)
	{
		*len = -1;
		ft_putchar('A');
		return ;
	}
	ft_printf("Estoy en el nodo %s y voy a anyadirle el nodo %s que tiene i = %i\n", map->path->node->name, map->path->node->links[i]->name, i);
	tmp_path = ft_new_path(map->path->node->links[i], map->path, &(map->len));
	map->path->node->links[i]->ihbt = pos;
	i++;
	while (n_links - i > 0)
	{
		while (i <= n_links - 1 && map->path->node->links[i]->ihbt == pos)
		{
			ft_printf("El nodo %s tiene pos=%i\n", map->path->node->links[i]->name, map->path->node->links[i]->ihbt);
			i++;
		}
		if (i > n_links - 1)
			break ;
		while(map->path->prev)
			map->path = map->path->prev;
		tmp_map->next = ft_new_map(ft_new_path(map->path->node, NULL, 0), tmp_map);
		tmp_map = tmp_map->next;
		while (map->path->next)
		{
			ft_printf("Voy a copiar el nodo %s delante de %s\n",map->path->next->node->name, tmp_map->path->node->name);
			map->path = map->path->next;
			tmp_map->path->next = ft_new_path(map->path->node, tmp_map->path, &(tmp_map->len));
			tmp_map->path = tmp_map->path->next;
		}
//		if (map->path->prev && map->path->node->links[i]->id == map->path->prev->node->id)

		ft_printf("He copiado el nodo %s y voy a anyadirle el nodo %s que tiene i = %i\n", tmp_map->path->node->name, map->path->node->links[i]->name, i);
		tmp_map->path->next = ft_new_path(map->path->node->links[i], tmp_map->path, &(tmp_map->len));
		tmp_map->path = tmp_map->path->next;
		tmp_map->path->node->ihbt = pos;
		i++;
	}
	map->path->next = tmp_path;
	map->path = map->path->next;
//	if (map->path->prev && map->path->node->links[i]->id == map->path->prev->node->id)

	
}

static int	destroy_path(t_map **map, int pos)
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
	if (!(*map)->path)
		ft_putstr("Es nulo, bien\n");
	if ((*map)->next)
	{
			ft_printf("El anterior es %s y el siguiente es %s\n",(*map)->prev->path->node->name, (*map)->next->path->node->name);
		(*map)->next->prev = (*map)->prev;
		(*map)->prev->next = (*map)->next;
	}
	else
	{
		ft_printf("El anterior es %s\n",(*map)->prev->path->node->name);
		(*map)->prev->next = NULL;
	}
	if ((*map)->next)
		*map = (*map)->next;
	else
		*map = (*map)->prev;
	free(tmp);
	ft_printf("Ahora estoy en el nodo %s\n", (*map)->path->node->name);
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
	t_map	*map;
	t_map	*tmp_map;
	int		pos;

	pos = 1;
	map = ft_new_map(ft_new_path(graf, NULL, 0), NULL);
	tmp_map = map;
	map->path->node->ihbt = 1;
	while ((pos = check_paths(&tmp_map, pos)) >= 0)
	{
//		if (tmp_map->path->node->start && tmp_map->len > 1 && tmp_map->path->prev)
		if (tmp_map->len < 0)
		{
			ft_printf("DELETING\n");
			ft_printf("Estoy en el nodo %s y la longitud del path por ahora es %i\n", tmp_map->path->node->name, tmp_map->len);
			pos = destroy_path(&tmp_map, pos);
			ft_printf("DELETED\n");
		}
		//	else if (tmp_map->path->node->n_links > 2 || (tmp_map->path->node->n_links > 1 && tmp_map->path->node->start))
		else
		{
			ft_printf("COPYING\n");
			ft_printf("Estoy en el nodo %s que tiene %i links\n", tmp_map->path->node->name, tmp_map->path->node->n_links);
			copy_paths(tmp_map, tmp_map->path->node->n_links, pos, &(tmp_map->len));
			ft_printf("COPIED\n");
			ft_printf("Ahora estoy en el nodo %s\n", tmp_map->path->node->name);
		}
/* 		else if (!tmp_map->path->node->end) */
/* 		{ */
/* 			ft_printf("ADDING\n"); */
/* //			if (tmp_map->path->prev && tmp_map->path->node->links[0]->id == tmp_map->path->prev->node->id) */
/* 			tmp_map->path->node->ihbt = 1; */
/* 			if (map->path->node->links[1]->ihbt == pos) */
/* 			{ */
/* 				ft_printf("Estoy en el nodo %s y voy a anyadir el nodo %s\n", tmp_map->path->node->name, tmp_map->path->node->links[1]->name); */
/* 				tmp_map->path->next = ft_new_path(tmp_map->path->node->links[1], tmp_map->path, &(tmp_map->len)); */
/* 				tmp_map->path = tmp_map->path->next; */
/* 			} */
/* 			else if (!map->path->node->links[0]->ihbt == pos) */
/* 			{ */
/* 				ft_printf("Estoy en el nodo %s y voy a anyadir el nodo %s\n", tmp_map->path->node->name, tmp_map->path->node->links[0]->name); */
/* 				tmp_map->path->next = ft_new_path(tmp_map->path->node->links[0], tmp_map->path, &(tmp_map->len)); */
/* 				tmp_map->path = tmp_map->path->next; */
/* 			} */
/* 			else */
/* 				destroy_path(&tmp_map); */
/* 			ft_printf("ADDED\n"); */
/* 		} */
		//	ft_map_lector(map, NULL);
	}
	return (map);
}
