/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:05:02 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/16 07:35:52 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"

typedef struct		s_node
{
	char			*name;
	int				id;
	int				ants;
	int				start : 1;
	int				end : 1;
	int				ihbt : 1;
	int				n_links;
	struct s_node	*links;
}									t_node;

typedef struct		s_errors
{
	unsigned int	start : 1;
	unsigned int	end : 1;
}									t_error;

typedef struct		s_path
{
	t_node			*node;
	struct	s_path			*next;
	struct	s_path			*prev;
}									t_path;

typedef struct		s_data
{
	int				fd;
	int				n_ants;
	t_node		*start;
	t_error		errors;
}									t_data;

t_node			*ft_reader(t_data *data);

#endif
