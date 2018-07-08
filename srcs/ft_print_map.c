/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:38:04 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/08 22:35:33 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void		resize_file(t_data *data)
{
	char 	*aux;
	int		pos;

	pos = data->file_len;
	if (!(aux = (char *)ft_memalloc(sizeof(char) * (PRINT_MAP_BUFF * (pos / PRINT_MAP_BUFF + 1)))))
		ft_error(NULL);
	while (pos - 1 >= 0)
	{
		aux[pos - 1] = (data->file)[pos - 1];
		pos--;
	}
	free(data->file);
	data->file = aux;
}

void			ft_print_map(t_data *data, char *line)
{
	while (*line)
	{
		if (!(data->file_len % PRINT_MAP_BUFF))
			resize_file(data);
		data->file[data->file_len] = *line;
		data->file_len++;
		line++;
	}
	if (!(data->file_len % PRINT_MAP_BUFF))
		resize_file(data);
	data->file[data->file_len++] = '\n';
}
