/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_lector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 08:12:53 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/22 17:27:05 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	path_lector(t_path *path)
{	
	while(path)
	{
		ft_printf("%s - ", path->node->name);
		path = path->next;
	}
}

void	ft_map_lector(t_map *map, t_node *graf)
{
	int		i;
	
	i = 1;

	
	if (map)
	{
		while (map->path)
		{
			ft_printf("Path %i:\n", i);
			path_lector(map->path);
			i++;
			map++;
			ft_putchar('\n');
		}
		
	}
	else
	{
		while (graf)
		{
			i = 0;
			if (graf->n_links)
				ft_printf("%s: ",graf->name);
			while (i < graf->n_links)
				ft_printf("%s, ",graf->links[i++]->name);
			if (graf->n_links)
				ft_putstr("\n");
			graf = graf->next;
		}
	}
	return ;
}
