/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:32:11 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/16 05:26:32 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		main(int argc, char **argv)
{
	t_data	data;
  t_node	*node;

	data = (t_data){1, 0, NULL, (t_error){0, 0, 0}};
	if (argc >= 2 && (data.fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
  node = ft_reader(&data);
	while (node)
	{
		ft_putstr(node->name);
		ft_putstr("\n");
		node = node->links;
	}
	return (0);
}
