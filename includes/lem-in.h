/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:05:02 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/18 20:02:50 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include </Users/mrodrigu/.brew/include/SDL2/SDL.h>
# include </Users/mrodrigu/.brew/include/SDL2/SDL_image.h>
# include "../libft/includes/libft.h"

#define LINK_BUFF 10

typedef struct		s_node
{
	char			*name;
	int				id;
	int				ants;
	int				start : 1;
	int				end : 1;
	int				ihbt;
	int				n_links;
	struct s_node	**links;
	struct s_node	*next;
}									t_node;

typedef struct		s_errors
{
	unsigned int	start : 1;
	unsigned int	end : 1;
}									t_error;

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

typedef struct		s_conj
{
	int				cuant;
	t_map			**path;
}					t_conj;

typedef struct		s_data
{
	int				fd;
	int				n_ants;
	int				current_line;
	int				n_nodes;
	t_node			*start;
	t_node			*end;
	t_error			errors;
}									t_data;

t_node			*ft_reader(t_data *data);
void				ft_line_error(int n, char *err);
void			ft_depure_graf(t_node *graf);
//t_map			*ft_search_paths(t_node *graf);
void			ft_map_lector(t_map *map, int mode, t_node *graf);

#endif
