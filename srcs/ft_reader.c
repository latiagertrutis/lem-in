/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:04:22 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/02 19:24:56 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_node			*ft_reader(t_data *data)
{
	char		*line;
	t_node		*head;

	ft_check_number_of_ants(data, &line);
	if (!(head = (t_node *)ft_memalloc(sizeof(t_node))) ||
		!(head->links = (t_node **)ft_memalloc(sizeof(t_node *) * LINK_BUFF)))
		ft_error(NULL);
	line = ft_ini_node(data, head, line);
	if (!data->start || !data->end)
		ft_line_error(data->current_line, "No start or end found");
	ft_set_links(data, line, head);
	ft_putstr("\n");
	return (head);
}
