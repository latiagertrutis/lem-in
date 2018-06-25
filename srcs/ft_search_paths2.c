/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_paths2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:23:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/25 15:40:45 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_path	*new_path(t_node *node, t_path *next, int *len)
{
	t_path	*path;
	
	if (!(path = (t_path *)ft_memalloc(sizeof(t_path))))
		ft_error("Error malloc ft_new_path\n");
	path->next = next;
	path->prev = NULL;
	path->node = node;
	node->ihbt = -1;
	if (len)
		(*len)++;
	return (path);
}

static t_path	*realoj(t_path *src, int len)
{
	t_path *new;

	if (!(new = (t_path *)ft_memalloc(sizeof(t_path) * (len + 1001))))
		ft_error("Error malloc en realoj\n");
	while (len)
	{
		new[len] = src[len];
		len--;
	}
	return (new);
}

static t_map	*make_path(t_path *bfs, int end, int len)
{
	t_map	*conj;
	t_map	*head;
	t_path	*tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!(conj = (t_map *)ft_memalloc(sizeof(t_map))))
		ft_error("Error malloc ft_search_paths2\n");
	head = conj;
	while (end)
	{
		if (bfs[len - ++i].node->end)
		{
			if (!conj)
				if (!(conj = (t_map *)ft_memalloc(sizeof(t_map))))
					ft_error("Error malloc ft_search_paths2\n");
			conj->path = new_path(bfs[len - i].node, NULL, &(conj->len));
			conj->tail = conj->path;
			tmp = bfs + len - i;
			end--;
			while (!conj->path->node->start)
			{
				ft_printf("Estoy en %s\n", conj->path->node->name);
				conj->path->prev = new_path(tmp->prev->node, conj->path, &(conj->len));
				conj->path = conj->path->prev;
				ft_printf("Estoy en %s\n", conj->path->node->name);
				tmp = tmp->prev;
			}
			conj = conj->next;
		}
	}
	free(bfs);
	conj = head;
	ft_map_lector(conj, NULL);
	return (conj);
}

static t_path	*ini_bfs(int *i, int *len, t_node *start)
{
	t_path *bfs;
	
	if (!(bfs = (t_path *)ft_memalloc(1000 * sizeof(t_path))))
		ft_error("Error malloc ft_search_paths2\n");
	bfs[0].node = start;
	bfs[0].node->ihbt = 1;
	bfs[0].prev = NULL;
	*i = -1;
	*len = 0;
	return (bfs);
}

t_map	*ft_search_paths2(t_node *start, int *end, int max)
{
	t_path	*bfs;
	int		len;
	int		i;
	int		j;
	int		t;
	int		flag;

	bfs = ini_bfs(&i, &len, start);
	while (!bfs[++i].node->end)
	{
		j = -1;
		flag = 0;
		t = 0;
//		ft_printf("max = %i, len = %i, i = %i\n", max, len, i);
		if (max == bfs[i].node->ihbt + 1)
		{
			ft_printf("El tamanyo SI importa\n");
			flag = 1;
			while (t < bfs[i].node->n_links && !bfs[i].node->links[t]->end)
				t++;
			ft_printf("El nodo %s tiene t = %i\n",bfs[i].node->name, t);
		}
		while(++j < bfs[i].node->n_links && (t == bfs[i].node->n_links || !t))
		{
			ft_printf("Estoy en %s y esta unido con %s que tiene ihbt=%i\n", bfs[i].node->name, bfs[i].node->links[j]->name,bfs[i].node->links[j]->ihbt);

			ft_printf("max = %i, len = %i, i = %i, j=%i\n", max, len, i, j);

			if (!bfs[i].node->links[j]->ihbt && !bfs[i].node->links[j]->start)
			{
				ft_putstr("CACA\n");
				ft_printf("Voy a anyadir el nodo %s\n", bfs[i].node->links[j]->name);
				flag = 1;
				if (!((len + 1) % 1000))
					bfs = realoj(bfs, len);
				bfs[++len].node = bfs[i].node->links[j];
				bfs[len].prev = bfs + i;
				if (bfs[len].node->end)
					(*end)++;
				else
					bfs[len].node->ihbt = bfs[i].node->ihbt + 1;
			}
			ft_putchar('B');			
		}
		if (i + 1 > len)
			return (NULL);
	}
	return (make_path(bfs, *end, len));
}
