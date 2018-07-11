/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:32:11 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/11 03:32:14 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_map		**check_insta_win(t_data *data, int *min)
{
	int		i[2];
	t_map	**paths;

	i[0] = 0;
	i[1] = 0;
	while (i[0] < data->start->n_links)
		if (data->start->links[i[0]++]->end)
			i[1] = 1;
	if (!i[1])
		return (NULL);
	if (!(paths = (t_map **)ft_memalloc(sizeof(t_map *))))
		ft_error(NULL);
	if (!(*paths = (t_map *)ft_memalloc(sizeof(t_map))))
		ft_error(NULL);
	if (!((*paths)->path = (t_path *)ft_memalloc(sizeof(t_path))))
		ft_error(NULL);
	(*paths)->path->node = data->start;
	if (!((*paths)->path->next = (t_path *)ft_memalloc(sizeof(t_path))))
		ft_error(NULL);
	(*paths)->path->next->node = data->end;
	(*paths)->path->next->prev = (*paths)->path;
	(*paths)->tail = (*paths)->path->next;
	*min = 1;
	return (paths);
}

static void			check_arguments(t_data *data, int *argn, char ***argv)
{
	if (*argn > 3 || (*argn == 3 && ft_strcmp((*argv)[1], "-f")))
	{
		ft_putstr_fd("Usage: ./lem-in [option] < File Name or ./lem-in", 2);
		ft_error(" [option] file_name |options: -f[only shortest path]");
	}
	else if (*argn == 3)
	{
		data->short_path = 1;
		(*argv)++;
	}
	else if (*argn == 2)
	{
		if (!ft_strcmp((*argv)[1], "-f"))
		{
			data->short_path = 1;
			(*argv)++;
			(*argn)--;
		}
	}
}

static t_map		**main_core(int *min, t_data *data, t_node *node)
{
	t_map	**paths;
	t_map	*map;

	if (!(paths = check_insta_win(data, min)))
	{
		if (!(map = ft_depure_graf(data, node)))
		{
			*min = ft_min(data->end->n_links, data->start->n_links);
			paths = ft_algorithm(data, node, *min);
			ft_prepare_conjunts(paths, ft_min(data->start->n_links,
				data->end->n_links));
		}
		else
		{
			if (!(paths = (t_map **)malloc(sizeof(t_map *))))
				ft_error("Error malloc main\n");
			*paths = map;
			(*paths)->path->prev = (t_path *)ft_memalloc(sizeof(t_path));
			(*paths)->path->prev->next = (*paths)->path;
			(*paths)->path->prev->node = data->start;
			(*paths)->path = (*paths)->path->prev;
			*min = 1;
		}
	}
	return (paths);
}

int					main(int argc, char **argv)
{
	t_data	data;
	t_node	*node;
	t_map	**paths;
	int		min;

	min = 0;
	paths = NULL;
	data = (t_data){0, NULL, 0, 0, 1, 0, NULL, NULL, (t_error){0, 0}, 0};
	check_arguments(&data, &argc, &argv);
	if (argc > 1 && (data.fd = open(argv[1], O_RDONLY)) < 0)
		ft_error(NULL);
	node = ft_reader(&data);
	paths = main_core(&min, &data, node);
	write(1, data.file, data.file_len);
	ft_putstr("\n");
	ft_distribute_ants(&data, paths, min);
	free_info(node, paths, min);
	free(data.file);
	return (0);
}
