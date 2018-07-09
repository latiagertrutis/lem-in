/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:32:11 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/09 03:43:31 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void			free_node(t_node *node)
{
	t_node *n_aux;

	while (node)
	{
		n_aux = node;
		node = node->next;
		free(n_aux->name);
		free(n_aux->links);
		free(n_aux);
	}
}

static void			free_info(t_node *node, t_map **paths, int min)
{
	t_path	*aux;
	t_path	*aux2;
	t_map	*m_aux;
	int		i;

	free_node(node);
	i = -1;
	while (++i < min)
	{
		while (paths[i])
		{
			aux = paths[i]->tail;
			while (aux)
			{
				aux2 = aux;
				aux = aux->prev;
				free(aux2);
			}
			m_aux = paths[i];
			paths[i] = paths[i]->next;
			free(m_aux);
		}
		free(paths[i]);
	}
	free(paths);
}

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

int					main(int argc, char **argv)
{
	t_data	data;
	t_node	*node;
	t_map	**paths;
	int		min;

	min = 0;
	paths = NULL;
	data = (t_data){0, NULL, 0, 0, 1, 0, NULL, NULL, (t_error){0, 0}};
	if (argc >= 2 && (data.fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	node = ft_reader(&data);
	if (!(paths = check_insta_win(&data, &min)))
	{
		ft_depure_graf(&data, node);
		min = ft_min(data.end->n_links, data.start->n_links);
		paths = ft_algorithm(&data, node, min);
		ft_prepare_conjunts(paths, ft_min(data.start->n_links,
			data.end->n_links));
	}
	write(1, data.file, data.file_len);
	ft_putstr("\n");
	ft_distribute_ants(&data, paths, min);
	free_info(node, paths, min);
	free(data.file);
	return (0);
}
