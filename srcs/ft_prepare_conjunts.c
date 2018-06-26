/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_conjunts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 21:47:21 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/27 01:16:13 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void		show_path(t_path *path)
{
	while (path)
	{
		ft_printf("%s - ", path->node->name);
		path = path->next;
	}
	ft_printf("\n");
}

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
			ft_printf("len = %i\n", paths_tmp->len);
			show_path(paths_tmp->path);
			if (paths_tmp->len < 0)
			{
				paths_tmp->len *= -1;
				paths_tmp = paths_tmp->next;
			}
			else
			{
				ft_printf("borro\n");
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
		ft_printf("avanzo\n");
		i++;
	}
} 
