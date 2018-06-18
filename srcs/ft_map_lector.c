/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_lector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 08:12:53 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/17 10:55:02 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_map_lector(t_map *map, int mode, t_node *graf)
{
	int		i;

	i = 1;

	if (mode)
	{
		while (map)
		{
//			ft_printf("Path %i:\n", i);
			while(map->path)
			{
//				ft_printf("%s - ", map->path->node->name);
				map->path = map->path->next;
			}
			i++;
			map = map->next;
			ft_putchar('\n');
		}
	}
	else
	{
		while (graf->name)
		{
			i = 1;
			ft_putstr(graf->name);
			ft_putstr(": ");
			while (i <= graf->n_links)
			{
				ft_putstr((graf->links[i++]).name);
				ft_putstr(", ");
			}
				ft_putstr("\n");
				graf = graf->links;
		}
	}
	return ;
}
