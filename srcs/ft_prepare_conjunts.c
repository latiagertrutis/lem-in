/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_conjunts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 21:47:21 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/30 15:54:00 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void		move_path(t_map **paths_tmp)
{
	t_path *tmp;

	while ((*paths_tmp)->path)
	{
		tmp = (*paths_tmp)->path->next;
		free((*paths_tmp)->path);
		(*paths_tmp)->path = tmp;
	}
}

static void		delete_path(t_map **paths_tmp, t_map **paths)
{
	t_map	*map_tmp;

	move_path(paths_tmp);
	map_tmp = (*paths_tmp);
	if (!(*paths_tmp)->prev)
	{
		(*paths_tmp) = (*paths_tmp)->next;
		(*paths_tmp)->prev = NULL;
		paths = &(*paths_tmp);
	}
	else if (!(*paths_tmp)->next)
	{
		(*paths_tmp)->prev->next = NULL;
		(*paths_tmp) = NULL;
	}
	else if ((*paths_tmp)->prev && (*paths_tmp)->next)
	{
		(*paths_tmp)->prev->next = (*paths_tmp)->next;
		(*paths_tmp)->next->prev = (*paths_tmp)->prev;
		(*paths_tmp) = (*paths_tmp)->next;
	}
	else
		(*paths_tmp) = NULL;
	free(map_tmp);
}

void			ft_prepare_conjunts(t_map **paths, int max)
{
	int		i;
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
				delete_path(&(paths_tmp), paths + i);
		}
		i++;
	}
}
