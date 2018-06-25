/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_conjunts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 21:47:21 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/25 23:42:10 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_prepare_conjunts(t_map **paths, int max)
{
	int		i;
	t_map	*tmp;
	t_map	*tmp2;

	i = 0;
	while (i < max)
	{
		tmp = paths[i];
		while (tmp)
		{
			tmp2 = tmp->next;
			if (tmp->len > 0)
				ft_destroy_path(tmp, 0);
			else if(tmp->len < 0)
				tmp->len *= -1;
			tmp = tmp2;
		}
		i++;
	}
}
 
