/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_depure_graf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 08:18:55 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/18 13:01:24 by mrodrigu         ###   ########.fr       */
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
		graf = graf->links[0];
		graf->n_links--;
	}
	i = 0;
	while (graf->links[i]->id != tmp->id)
		i++;
	while (graf->links + ++i)
		graf->links[i - 1] = graf->links[i];
	graf->links[i] = NULL;
}

static int		check_useless_nodes(t_node *graf)
{
	t_node	*tmp;
	t_node	*tmp2;
	int		i;
	int		j;

	tmp = graf->links[0];
	tmp2 = graf->links[1];
//	ft_printf("El nodo %s esta unido con %s y %s \n", graf->name, tmp->name, tmp2->name);
	if (tmp->start || tmp->end || tmp2->start || tmp2->end)
		return (0);
	i = 0;
//	ft_putchar('B');
	while (i < tmp->n_links)
	{
//		ft_putchar('A');
		j = 0;
		while (j < tmp2->n_links && tmp->links[i]->id != tmp2->id)
		{
			if (tmp->links[i]->id == tmp2->links[j]->id && tmp->links[i]->id
			    != graf->id && tmp->links[i]->n_links == 2 &&
			    tmp2->links[j]->id != tmp->id)
			{
				tmp->links[i]->n_links = 0;
				tmp->links[i] = tmp2->links[j];
				tmp2->links[j] = tmp->links[i];
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
//	ft_putnbr(graf->n_links);
	while (graf->name)
	{
		if (!(graf->start) && !(graf->end) && graf->n_links == 2)
		{
			if (check_useless_nodes(graf))
				graf = head;
		}
		else
			graf = graf->next;
	}
	graf = head;
	return ;
	while (graf->name)
	{
		if (!graf->start && !graf->end && graf->n_links == 1)
		{
			kill_branch(graf);
			graf = head;
		}
		else
			graf = graf->next;
	}
}
