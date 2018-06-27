/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:35:46 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/27 11:38:44 by jagarcia         ###   ########.fr       */
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

static t_map		*prepare_graf(t_node *node, t_map *map, int pos, int mode)
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
	map->len *= -1;
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
	while(tmp->next)
		tmp = tmp->next;
	
	return (tmp);
}
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

static void	reset_graf(t_node *node, int *cuant)
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

t_map	**ft_algorithm(t_data *data, t_node *node)
{
	t_map	**conj;
	t_map	*prev;
	t_map	*tail;
	t_map	*head;
	int		i;
	int		j;
	int		k;
	int		tmp;
	int		cuant;
	int		tmp_cuant;
	int		max;

	prev = NULL;
	max = ft_min(data->start->n_links, data->end->n_links);
	conj = (t_map **)ft_memalloc(sizeof(t_map *) * (max + 1));
	conj[max] = NULL;
	tmp = 0;
	i = 0;
	cuant = 0;
	j = max;
	tail = NULL;
	while (i < data->start->n_links && i >= 0 && j > 0)
	{
		data->start->ihbt = 1;
		data->start->links[i]->start = 0x1;
		if (!(conj[max - j] = ft_search_paths2(data->start->links[i], &tmp_cuant, &tmp)))
		{
			i--;
			if (head)
			{
				conj[max - j] = head;
			}
			prev = NULL;
			if (!(cuant - 1) || tail->path->node->id != tail->prev->path->node->id)
				{
					if ((tmp = tail->len) < 0)
						tmp *= -1;
				}
				else
					tmp = 0;
			prepare_graf(node, conj[max - j], --cuant, 0);
			tail = ft_destroy_path(&head, cuant + 1);
		}
		data->start->links[i]->start = 0;
		if (conj[max - j] && i + 1 == max - j + 1)
		{
			k = 0;
			conj[max - j]->len *= -1;
			if (prev)
			{
				prev->next = conj[max - j];
				conj[max - j]->prev = prev;
			}
			while (conj[max - j]->prev)
			{
				conj[max - j] = conj[max - j]->prev;
			}
			head = NULL;
			tail = NULL;
			prev = NULL;
			reset_graf(node, &cuant);
			i = 0;
			j--;
		}
		else if (!tmp)
		{
			cuant += tmp_cuant;
			tmp_cuant = 0;
			tmp = 0;
			i++;
			if (!head)
				head = conj[max - j];
			if (prev)
			{
				tail->next = conj[max - j];
				conj[max - j]->prev = tail;
				ft_map_lector(head, NULL);
			}
			tail = prepare_graf(node, head, cuant - 1, 1);
			prev = tail;
			conj[max - j] = tail->next;
		}
	}
	return (conj);
}
