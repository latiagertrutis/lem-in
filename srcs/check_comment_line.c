/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comment_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 12:15:36 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/02 19:15:09 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_comment_line(t_data *data, char *line, t_node *node)
{
	if (*line == 35)
	{
		if (!ft_strcmp(line, "##start"))
		{
			if (data->errors.start || !node)
				ft_line_error(data->current_line,
								"Wrong number or position of ##start");
			data->errors.start = 0x1;
		}
		else if (!ft_strcmp(line, "##end"))
		{
			if (data->errors.end || !node)
				ft_line_error(data->current_line,
								"Wrong number or position of ##end");
			data->errors.end = 0x1;
		}
		return (1);
	}
	return (0);
}
