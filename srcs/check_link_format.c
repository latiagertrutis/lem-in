/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_link_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 00:02:17 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/29 00:02:46 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_link_format(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '-')
	{
		if (line[i] < 33 || line[i] > 126)
			return (1);
		i++;
	}
	if (!line[i++])
		return (1);
	while (line[i] && line[i] != '-')
	{
		if (line[i] < 33 || line[i] > 126)
			return (1);
		i++;
	}
	return (0);
}
