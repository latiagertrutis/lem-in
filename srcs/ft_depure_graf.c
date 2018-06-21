/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_depure_graf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 08:18:55 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/20 17:11:47 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lem-in.h"

static void		move_links(t_node *graf, int pos)
{
	while (pos + 1 < graf->n_links)
	{
		graf->links[pos] = graf->links[pos + 1];
		pos++;
	}
	graf->links[pos] = NULL;
	graf->n_links--;
}

static void		kill_branch(t_node *graf)
{
	int	i;
	t_node	*tmp;

	while (graf->n_links == 1)
	{
		graf->n_links--;
		tmp = graf;
		graf = graf->links[0];
	}
	i = 0;
	while (graf->links[i]->id != tmp->id)
		i++;
	move_links(graf, i);
}

static int		check_useless_nodes(t_node *graf)
{
	t_node	*tmp;
	t_node	*tmp2;
	int		i;
	int		j;

	tmp = graf->links[0];
	tmp2 = graf->links[1];
	if (tmp->start || tmp->end || tmp2->start || tmp2->end)
		return (0);
	i = 0;
	while (i < tmp->n_links)
	{
		j = 0;
		while (j < tmp2->n_links && tmp->links[i]->id != tmp2->id)
		{
			if (tmp->links[i]->id == tmp2->links[j]->id && tmp->links[i]->id
			    != graf->id && tmp->links[i]->n_links == 2 &&
			    tmp2->links[j]->id != tmp->id)
			{
				tmp->links[i]->n_links = 0;
				move_links(tmp, i);
				move_links(tmp2, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_depure_graf(t_node *graf)
{
	t_node *head;

	head = graf;
	while (graf)
	{
		if (!(graf->start) && !(graf->end) && graf->n_links == 2)
		{
			if (check_useless_nodes(graf))
				graf = head;
		}
		graf = graf->next;
	}
	graf = head;
	while (graf)
	{
		if (!graf->start && !graf->end && graf->n_links == 1)
		{
			kill_branch(graf);
			graf = head;
		}
		graf = graf->next;
	}
	graf = head;
	while (graf)
	{
		if (!(graf->start) && !(graf->end) && graf->n_links == 2)
		{
			if (check_useless_nodes(graf))
				graf = head;
		}
		graf = graf->next;
	}
}
