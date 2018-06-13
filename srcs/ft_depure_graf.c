/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_depure_graf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 08:18:55 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/13 09:38:30 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lem-in.h"

static void		kill_branch(t_node *graf)
{
	int	i;
	t_node	*tmp;

	while (graf->n_links == 1)
	{
		graf->ihbt = 1;
		tmp = graf;
		graf = graf->links[1];
		graf->n_links--;
	}
	i = 1;
	while (graf->links[i]->id != tmp->id)
		i++;
	while (graf->links[++i])
		graf->links[i - 1] = graf->links[i];
	graf->links[i] = NULL;
}

static void		check_useless_ways(t_node *graf)
{
	t_node	*tmp;
	t_node	*tmp2;
	int		i;

	tmp = graf->links[1];
	tmp2 = graf->links[2];
	if (tmp->start || tmp->end || tmp2->start || tmp2->end)
		return ;
	i = 1;
	while (i < tmp->n_links)
	{
		while (j < tmp2->n_links)
		{
			if (tmp->links[i]->id == tmp2->links[j]->id && tmp->links[i]->id != graf->id && tmp->links[i]->n_links == 2)
			{
				graf->n_links = 0;
				tmp->links[i] = tmp2->links[j];
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_depure_graf(t_node *graf)
{
	t_node *head;

	head = graf;
	while (graf)
	{
		if (!start && !end && n_links == 2)
			check_useless_ways(graf);
		graf = graf->links[0];
	}
	graf = head;
	while (graf)
	{
		if (!start && !end && n_links == 1)
			kill_branch(graf);
		graf = graf->links[0];
	}
	depurator(graf);
}
