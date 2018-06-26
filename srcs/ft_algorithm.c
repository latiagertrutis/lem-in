/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:35:46 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/26 12:55:56 by jagarcia         ###   ########.fr       */
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

static void		prepare_graf(t_node *node, t_map *map, int pos, int mode)
{
	t_path *path;

	while (pos--)
		map = map->next;
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
}
void	ft_destroy_path(t_map *map, const int n)
{
	int		i;
	t_path	*aux;
	t_map	*prev;
	t_map	*next;

	i = 0;
	while (i < n - 1 && map)
	{
		map = map->next;
		i++;
	}
	next = map->next;
	prev = map->prev;
	while (map->path)
	{
		aux = map->path->next;
		free(map->path);
		map->path = aux;
	}
	if (map->prev && map->next)
	{
		map->prev->next = map->next;
		map->next->prev = map->prev;
	}
	else if (map->prev && !map->next)
		map->prev->next = map->next;
	else if (!map->prev && map->next)
		map->next->prev = map->prev;
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

static int	algorithm_FUNC(t_map *map, void *data, int FUNC)
{
	t_map	*prev;
	int		*cuant;
	int		tmp;
	
	if (FUNC == PREV)
	{
		prev = (t_map *)data;
		if (prev)
		{
			prev->next = map;
			map->prev = prev;
		}
	}
	if (FUNC == CUANT0)
	{
		cuant = (int *)data;
		if (!*cuant)
		{
			tmp = map->len;
			ft_destroy_path(map, 0);
			return (tmp);
		}
	}
	return (0);
}


static void	ft_algorithm_core(t_map **conj, int *cuant, t_data *data, t_node *node)
{
	int		i;
	int		j;
	int		tmp;
	int		max;
	t_map	*prev;

	if (!(max = ft_min(data->start->n_links, data->end->n_links)))
		ft_error("Start y Exit no unidos\n");
	i = 0;
	j = max;
	prev = NULL;
	while (i < data->start->n_links && i >= 0 && j > 0)
	{
		data->start->ihbt = 1;
		data->start->links[i]->start = 0x1;
		if (!(conj[max - j] = ft_search_paths2(data->start->links[i], cuant + i, tmp)))
		{
			if (!i--)
				ft_error("Start y Exit no unidos\n");
			conj[max - j] = prev;
			prev = NULL;
			prepare_graf(node, conj[max - j], cuant[i], 0);
			if (cuant[i])
				ft_destroy_path(conj[max - j], cuant[i] + 1);
		}
		data->start->links[i]->start = 0;
		algorithm_FUNC(conj[max - j], prev, PREV);
//		algorithm_FUNC(conj[max - j], cuant + i, CUANT0);
		if (!cuant[i])
		{
			tmp = conj[max - j]->len;
			ft_destroy_path(conj[max - j], 0);
		}
		else if (conj[max - j] && i + 1 == max - j + 1)
		{
			conj[max - j]->len *= -1;
			while (conj[max - j]->prev)
				conj[max - j] = conj[max - j]->prev;
			reset_graf(node, data->start, cuant);
			j--;
			i = 0;
		}
		else
		{
			tmp = 0;
			prepare_graf(node, conj[max - j], --cuant[i++], 1);
			prev = conj[max - j];
			conj[max - j] = conj[max - j]->next;
		}
	}
}

t_map	**ft_algorithm(t_data *data, t_node *node)
{
	t_map	**conj;
	t_map	*prev;
	int		i;
	int		j;
	int		tmp;
	int		*cuant;
	int		max;

	prev = NULL;
	if (!(max = ft_min(data->start->n_links, data->end->n_links)))
		ft_error("Start y Exit no unidos\n");
	if (!(conj = (t_map **)ft_memalloc(sizeof(t_map *) * (max + 1))))
		ft_error("Error Malloc algorithm\n");
	if (!(cuant = (int *)ft_memalloc(sizeof(int) * data->start->n_links)))
		ft_error("Error Malloc algorithm\n");
	i = 0;
	j = max;
	ft_algorithm_core(conj, cuant, data, node);
	return (conj);
	/* while (i < data->start->n_links && i >= 0 && j > 0) */
	/* { */
	/* 	data->start->ihbt = 1; */
	/* 	data->start->links[i]->start = 0x1; */
	/* 	if (!(conj[max - j] = ft_search_paths2(data->start->links[i], cuant + i, tmp))) */
	/* 	{ */
	/* 		if (!i--) */
	/* 			ft_error("Start y Exit no unidos\n"); */
	/* 		conj[max - j] = prev; */
	/* 		prev = NULL; */
	/* 		prepare_graf(node, conj[max - j], cuant[i], 0); */
	/* 		if (cuant[i]) */
	/* 			ft_destroy_path(conj[max - j], cuant[i] + 1); */
	/* 	} */
	/* 	data->start->links[i]->start = 0; */
	/* 	if (prev) */
	/* 	{ */
	/* 		prev->next = conj[max - j]; */
	/* 		conj[max - j]->prev = prev; */
	/* 	} */
	/* 	if (!cuant[i]) */
	/* 	{ */
	/* 		tmp = conj[max - j]->len; */
	/* 		ft_destroy_path(conj[max - j], 0); */
	/* 	} */
	/* 	else if (conj[max - j] && i + 1 == max - j + 1) */
	/* 	{ */
	/* 		conj[max - j]->len *= -1; */
	/* 		while (conj[max - j]->prev) */
	/* 			conj[max - j] = conj[max - j]->prev; */
	/* 		reset_graf(node, data->start, cuant); */
	/* 		j--; */
	/* 		i = 0; */
	/* 	} */
	/* 	else */
	/* 	{ */
	/* 		tmp = 0; */
	/* 		prepare_graf(node, conj[max - j], --cuant[i++], 1); */
	/* 		prev = conj[max - j]; */
	/* 		conj[max - j] = conj[max - j]->next; */
	/* 	} */
	/* } */
	/* return (conj); */
}
