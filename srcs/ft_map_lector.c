/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_lector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 08:12:53 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/17 08:17:17 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_map_lector(t_map *map)
{
	int		i;

	i = 1;
	while (map)
	{
		ft_printf("Path %i:\n", i);
		while(map->path)
		{
			ft_printf("%s - ", map->path->node->name);
			map->path = map->path->next;
		}
		i++;
		map = map->next;
		ft_putchar('\n');
	}
	return ;
}
