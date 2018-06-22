/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_group_sets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:52:06 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/22 15:07:32 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_map	**set_init(t_map **set, int n)
{
	t_map	**aux;
	int		i;

	if (!(aux = (t_map **)ft_memalloc(sizeof(t_map *) * (SET_BUFF * (n + 1)))))
		ft_error(NULL);
	i = 0;
	while (i < n)
	{
		aux[i] = set[i];
		i++;
	}
	free(set);
	return (aux);
}

static int		check_compatibility(t_map *head, t_map *path)
{
	head->head = head->head->next;
	path->head = path->head->next;
	while (head->head && head->head->node != path->head->node)
	{
		head->head = head->head->next;
		path->head = path->head->next;
	}
	if (path->head->node->end && head->head->node->end)
		return (1);
	return (0);
}

static void		update_set(t_map **set, t_map *path, int pos)
{
	if (!set[pos])
	{
		if (!(set[pos] = (t_map *)malloc(sizeof(t_map))))
			ft_error(NULL);
		(set[pos])->prev = NULL;
	}
	else
	{
		if (!(set[pos]->next = (t_map *)malloc(sizeof(t_map))))
			ft_error(NULL);
		set[pos]->next->prev = set[pos];
		set[pos] = set[pos]->next;
	}
	(set[pos])-> path = path->path;
	(set[pos])-> head = path->head;
	(set[pos])-> len = path->len;
	(set[pos])-> next = NULL;
}

t_map					**ft_group_sets(t_map *head, t_map *path)
{
	t_map **set;

	set = NULL;
	while(head && head->path->node->end)
	{
		if (head->len == path->len && check_compatibility(head, path))
		{
			if (!(head->len % SET_BUFF) || !set)
				set = set_init(set, head->len);
			update_set(set, path, path->len);
		}
	}
	return (set);
}
