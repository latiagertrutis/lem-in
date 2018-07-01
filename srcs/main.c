/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:32:11 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/02 00:59:57 by mrodrigu         ###   ########.fr       */
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

void	ft_map_lector(t_map *map)
{
	int		i;

	i = 1;
	if (map)
	{
		while (map)
		{
			ft_printf("Path %i longitud %i:\n", i, map->len);
			path_lector(map->path);
			i++;
			map = map->next;
			ft_putchar('\n');
		}
	}
	return ;
}

int		main(int argc, char **argv)
{
	t_data	data;
	t_node	*node;
	t_map	**paths;
	int		min;

	ft_putstr("\033[H\033[J");
	data = (t_data){0, 0, 1, 0, NULL, NULL, (t_error){0, 0}};
	if (argc >= 2 && (data.fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	node = ft_reader(&data);
	ft_depure_graf(&data, node);
	min = ft_min(data.end->n_links, data.start->n_links);
	ft_printf("min = %i\n", min);
	paths = ft_algorithm(&data, node, min);
	for (int i = 0; i < min; i++)
	{
		ft_map_lector(paths[i]);
	}
	ft_prepare_conjunts(paths, ft_min(data.start->n_links, data.end->n_links));
	ft_distribute_ants(&data, paths, min);
	return (0);
}
