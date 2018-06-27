/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_funcs1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 13:45:50 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/27 17:51:16 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_map	*ft_destroy_path(t_map **map)
{
	t_path	*aux;
	t_map	*tmp;
	t_map	*tmp2;

	tmp2 = *map;
	while ((*map)->next)
		(*map) = (*map)->next;
	while ((*map)->path)
	{
		aux = (*map)->path->next;
		free((*map)->path);
		(*map)->path = aux;
	}
	if ((*map)->prev)
	{
		(*map)->prev->next = NULL;
		tmp = (*map)->prev;
	}
	else
	{
		tmp = NULL;
		tmp2 = NULL;
	}
	free((*map));
	(*map) = tmp2;
	return (tmp);
}

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

static void		show_path(t_path *path)
{
	while (path)
	{
		ft_printf("%s - ", path->node->name);
		path = path->next;
	}
	ft_printf("\n");
}

t_map		*ft_prepare_graf(t_node *node, t_map *map, int pos, int mode)
{
	t_path *path;
	t_map	*tmp;

	tmp = map;
	while (pos)
	{
		map = map->next;
		pos--;
	}
	path = map->path;	
//	show_path(path);
	map->len *= -1;
	while (node)
	{
		if (node->start)
			node->ihbt = 0;
		else if ((node->ihbt && !mode && (node->ihbt != -1 || compare_path(node, path))) || node->end)
			node->ihbt = 0;
		else if (mode && node->ihbt != -1 && compare_path(node, path))
			node->ihbt = -1;
		else if (node->ihbt != -1)
			node->ihbt = 0;
		node = node->next;
	}
	while(tmp->next)
		tmp = tmp->next;
	
	return (tmp);
}

int		ft_no_path(t_node *node, t_map *(tail_head[2]), int *cuant, t_map **conj)
{
	int		tmp;
	
	if (tail_head[0])
		*conj = tail_head[0];
	tmp = 0;
	if (!(*cuant - 1) || tail_head[1]->path->node->id != tail_head[1]->prev->path->node->id)
		tmp = tail_head[1]->len;
	tmp < 0 ? tmp *= -1 : tmp;
	ft_prepare_graf(node, tail_head[0], --(*cuant), 0);
	tail_head[1] = ft_destroy_path(&tail_head[0]);
	return (tmp);
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
	*cuant = 0;
}
