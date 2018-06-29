/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_conjunts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 21:47:21 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/29 18:07:27 by mrodrigu         ###   ########.fr       */
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
			if (paths_tmp->len < 0)
			{
				paths_tmp->len *= -1;
				paths_tmp = paths_tmp->next;
			}
			else
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
					paths_tmp = paths_tmp->next;
					paths_tmp->prev = NULL;
					paths[i] = paths_tmp;
				}
				else if (!paths_tmp->next)
				{
					paths_tmp->prev->next = NULL;
					paths_tmp = NULL;
				}
				else if (paths_tmp->prev && paths_tmp->next)
				{
					paths_tmp->prev->next = paths_tmp->next;
					paths_tmp->next->prev = paths_tmp->prev;
					paths_tmp = paths_tmp->next;
				}
				else
					paths_tmp = NULL;
				free(map_tmp);
			}
		}
		i++;
	}
}
