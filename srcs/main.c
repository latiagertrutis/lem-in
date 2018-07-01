/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:32:11 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/30 23:06:04 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

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
	paths = ft_algorithm(&data, node, min);
	ft_prepare_conjunts(paths, ft_min(data.start->n_links, data.end->n_links));
	ft_distribute_ants(&data, paths, min);
	return (0);
}
