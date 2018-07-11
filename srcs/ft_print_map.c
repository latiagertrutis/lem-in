/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:38:04 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/09 01:35:48 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		resize_file(t_data *data)
{
	char	*aux;
	int		pos;
	int		size;

	size = PRINT_MAP_BUFF;
	if (!(aux = (char *)ft_memalloc(sizeof(char) * (size * (data->file_len /
															size + 1)))))
		ft_error(NULL);
	pos = data->file_len - 1;
	while (pos >= 0)
	{
		aux[pos] = (data->file)[pos];
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
