/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:05:02 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/09 00:34:47 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# define LINK_BUFF 50
# define SET_BUFF 50
# define ALGORITHM_BUFF 1000

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
}					t_node;

typedef struct		s_errors
{
	unsigned int	start : 1;
	unsigned int	end : 1;
}					t_error;

typedef struct		s_path
{
	t_node			*node;
	struct s_path	*next;
	struct s_path	*prev;
}					t_path;

typedef struct		s_map
{
	t_path			*path;
	t_path			*tail;
	int				len;
	struct s_map	*next;
	struct s_map	*prev;
}					t_map;

typedef struct		s_data
{
	int				fd;
	int				n_ants;
	int				current_line;
	int				n_nodes;
	t_node			*start;
	t_node			*end;
	t_error			errors;
}					t_data;

t_node				*ft_reader(t_data *data);
void				ft_line_error(int n, char *err);
void				ft_depure_graf(t_data *data, t_node *node);
t_map				*ft_search_paths(t_node *start, int *end, int *max);
void				ft_check_number_of_ants(t_data *data, char **line);
int					check_comment_line(t_data *data, char *line, t_node *node);
char				*ft_ini_node(t_data *data, t_node *node, char *line);
void				ft_set_links(t_data *data, char *line, t_node *head);
t_map				**ft_algorithm(t_data *data, t_node *node, int max);
t_map				**ft_algorithm_debug(t_data *data, t_node *node, int max);
double				ft_abs_double(double n);
int					distribute_ants(double **mat, int row, int col);
void				ft_prepare_conjunts(t_map **paths, int max);
int					ft_solve_system(double **mat, int row, int col);
int					ft_cuantity_of_ants(t_map *a, t_map *b, int a_len,
										int b_len);
void				ft_distribute_ants(t_data *data, t_map **conjs, int len);
void				ft_solution(t_data *data, t_map *conj, double **mat, int d);
t_map				*ft_destroy_path(t_map **map);
int					ft_finish_conjunt(t_map *(tail_head[2]), t_map **conj,
										t_node *node, int *cuant);
int					ft_prepare_next(t_map *(tail_head[2]), t_map **conj,
										int cuant, t_node *node);
t_map				*ft_destroy_path(t_map **map);
t_map				*ft_prepare_graf(t_node *node, t_map *map, int p, int mode);
int					ft_no_path(t_node *node, t_map *(tail_head[2]),
										int *cuant, t_map **conj);
void				ft_reset_graf(t_node *node, int *cuant);
t_path				*ft_realoj(t_path *src, int len);
int					ft_add_node(t_path **bfs, int *len, int i[3]);
void				ft_prepare_next_node(t_map **conj, t_path **tmp, int *end,
										t_path *ptr);
t_path				*ft_new_path(t_node *node, t_path *next, int *len);
void				resize_links(t_node *n);
int					check_link_format(char *line);
void				ft_cut_and_reset(t_node *true_start, int pos, t_node *node,
										int reset);
void	ft_map_lector(t_map *map);

#endif
