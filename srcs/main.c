/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:32:11 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/18 12:48:16 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		main(int argc, char **argv)
{
	t_data	data;
	t_node	*node;

	data = (t_data){0, 0, 1, 0, NULL, NULL, (t_error){0, 0}};
	if (argc >= 2 && (data.fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	node = ft_reader(&data);
	int i;
	while (node)
	{
		printf("name: %s | links: ", node->name);
		i = 0;
		while (i < node->n_links)
			printf("%s, ", (node->links[i++])->name);
		printf("\n");
		node = node->next;
	}


/* 	ft_map_lector(NULL, 0, node); */
/* 	ft_depure_graf(node); */
/* 	ft_printf("MAP DEPURED \n"); */
/* 	ft_map_lector(NULL, 0, node); */
/* //	ft_putstr(data.start->name); */
/* 	return (0); */
}
