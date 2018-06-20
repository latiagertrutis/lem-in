/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:32:11 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/18 17:04:27 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		main(int argc, char **argv)
{
	t_data	data;
	t_node	*node;
	t_map	*paths;

	data = (t_data){0, 0, 1, 0, NULL, NULL, (t_error){0, 0}};
	if (argc >= 2 && (data.fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	node = ft_reader(&data);
//	int i;
	/* while (node) */
	/* { */
	/* 	printf("id: %i | name: %s | links: ", node->id, node->name); */
	/* 	i = 0; */
	/* 	while (i < node->n_links) */
	/* 		printf("%s, ", (node->links[i++])->name); */
	/* 	printf("\n"); */
	/* 	node = node->next; */
	/* } */


//	ft_map_lector(NULL, node);
	ft_depure_graf(node);
	ft_printf("MAP DEPURED \n");
	ft_map_lector(NULL, node);
	paths = ft_search_paths(data.start);
	ft_printf("PATHS GENERATE \n");
	ft_map_lector(paths, NULL);
//	ft_putstr(data.start->name);
	return (0);
}
