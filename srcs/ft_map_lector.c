/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_lector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 08:12:53 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/27 11:16:17 by jagarcia         ###   ########.fr       */
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
		if (map->prev)
			ft_putstr("EL ANTERIOR NO ES NULO :S\n");
		while (map)
		{
			ft_printf("Path %i longitud %i:\n", i, map->len);
			path_lector(map->path);
			i++;
			map = map->next;
			ft_putchar('\n');
		}
		
	}
	else if (graf)
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
