/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_conjunts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 21:47:21 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/27 00:47:19 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_prepare_conjunts(t_map **paths, int max)
{
	int		i;
	t_path	*tmp;
	t_map	*map_tmp;
	t_map	*paths_tmp;

	i = 0;
	while (i < max)
	{
		paths_tmp = paths[i];
		while (paths_tmp)
		{
			if (paths_tmp->len >= 0)
			{
				while (paths_tmp->path)
				{
					tmp = paths_tmp->path->next;
					free(paths_tmp->path);
					paths_tmp->path = tmp;
				}
				map_tmp = paths_tmp;
				if (!paths_tmp->prev)
				{
					paths[i] = paths_tmp->next;
					paths[i]->prev = NULL;
				}
				else if (!paths_tmp->next)
					paths_tmp->prev->next = NULL;
				else if (paths_tmp->prev && paths_tmp->next)
				{
					paths_tmp->prev->next = paths_tmp->next;
					paths_tmp->next->prev = paths_tmp->prev;
				}
				else
					paths_tmp = NULL;
				paths_tmp = paths[i];
				free(map_tmp);
			}
			paths_tmp = paths_tmp->next;
		}
		i++;
	}
} 
