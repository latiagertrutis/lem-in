/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:05:02 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/09 01:04:26 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct		s_node
{
	char			*name;
	int				id;  // no entiendo la funcion de id si tienes *name o viceversa
	int				ant : 1; // en start pueden haber infinitas hormigas
	int				start : 1;
	int				end : 1;
//	int				n_links; // no hace falta solo necesitas que *links termine un NULL;
	struct s_node	*links;
}					t_node;

typedef struct		s_data
{
	int				fd;
}					t_data;

#endif
