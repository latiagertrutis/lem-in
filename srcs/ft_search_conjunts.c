/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_conjunts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 01:32:51 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/13 04:07:31 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lem-in.h"

static int	end_prox(t_node node, t_path *prev)
{
	int	i;

	if (!node.n_links)
		return (0);
	i = 1;
	if (node.n_links == 1)
	{
		while (i <= node.n_links)
		{
			if (node.links[i]->end)
				return (i);
			i++;
		}
	}
	while (i > 0 && node.links[i]->ihbt)
		i--;
	return (i);
}

int		ft_make_path(t_node graf, t_path *path)
{
	t_path *head;
	int		i;

	path = ft_new_node(NULL, &graf);
	head = path;
	i = 0;
	while (1)
	{
		graf.ihbt = 1;
		if (graf.end)
			break ;
		if ((i = end_prox(graf, path->prev)))
		{
			graf = graf.links[i];
			path->next = ft_new_node(path, graf);
			path = path->next;
		}
		else
		{
			if (graf.start)
			{
				free(head);
				return (0);
			}
			graf = path->prev->node;
			path = path->prev;
			ft_strdel(&(path->next));
		}
	}
	return (1);
}

int			ft_repair_way(t_node graf, t_path *path)

t_path		**ft_search_path(t_node graf, int cuant)
{
	int		i;
	int		j;
	t_path	**path;
	t_path	*head;

	path = (path **)ft_malloc(sizeof(path *) * cuant);
	i = 0;
	j = 0;
	while (j < cuant)
	{

		if (!(ft_make_way(graf, path[j])))
			ft_repair_way(graf, path[j - 1]);
		else
			j++;
	}
	return (path);
}
