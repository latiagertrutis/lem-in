/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_number_of_ants.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 12:08:50 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/30 23:07:55 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_check_number_of_ants(t_data *data, char **line)
{
	int			i;

	while (1)
	{
		if (get_next_line(data->fd, line) <= 0)
			ft_line_error(data->current_line, "Nothing in the map dude");
		ft_printf("%s\n", *line);
		if (!check_comment_line(data, *line, NULL))
			break ;
		data->current_line++;
	}
	i = 0;
	while ((*line)[i])
	{
		if (!ft_isdigit((*line)[i++]))
			ft_line_error(data->current_line,
							"First line should only contain numbers");
	}
	if (!(data->n_ants = ft_atoi(*line)))
		ft_line_error(data->current_line, "No ants");
}
