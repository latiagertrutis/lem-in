/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:05:02 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/17 08:12:37 by jagarcia         ###   ########.fr       */
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
	int				ihbt;
	int				n_links;
	struct s_node	*links;
}									t_node;

typedef struct		s_path
{
	t_node			*node;
	struct s_path	*next;
	struct s_path	*prev;
}					t_path;

typedef struct		s_map
{
	t_path			*path;
	int				*paz;
	int				len;
	struct s_map	*next;
	struct s_map	*prev;
}					t_map;

typedef struct		s_data
{
	int				fd;
	int				n_ants;
	t_node			*start;
}									t_data;

t_node			*ft_reader(t_data *data);

#endif
