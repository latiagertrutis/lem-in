/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:04:22 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/15 07:17:29 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static	void	ft_link(char *s1, char *s2, t_node *n, t_data *data)
{
	t_node	*aux;
	t_node	*aux2;
	t_node	*new_links;
	int		i;

	aux = n;
	while (aux && (i = ft_strcmp(aux->name, s1)))
		aux = aux->links;
	if (i)
		ft_error("Some name in links is wrong");
	if (!(new_links = (t_node *)malloc(sizeof(t_node) * (aux->n_links + 2))))
		return ;
	i = -1;
	while (aux->links && ++i < aux->n_links + 1)
		new_links[i] = aux->links[i];
	aux2 = n;
	while (aux2 && (i = ft_strcmp(aux2->name, s2)))
		aux2 = aux2->links;
	if (i)
		ft_error("Some name in links is wrong");
	new_links[aux->n_links + 1] = *aux2;
	free(aux->links);
	aux->links = new_links;
	aux->n_links++;
	if (aux->start)
	{
		aux->ants = data->n_ants;
		data->start = aux;
	}
}

static	void	ft_set_links(t_data *data, char *line, t_node *n)
{
	int i;

	while (1)
	{
		if (*line == 35)
			goto next;
		i = 0;
		while(line[i++] != '-');
		line[i - 1] = 0;
		ft_link(line, line + i, n, data);
		free(line);
	next: if (get_next_line(data->fd, &line) <= 0)
			break ;
	}
}

static char		*ft_ini_node(t_data *data, t_node *node, char *line)
{
	int		i;

	i = -1;
	while (get_next_line(data->fd, &line) > 0 && !ft_strchr(line, '-'))
	{
		if (*line == 35)
		{
			if (!ft_strcmp(line, "##start"))
				node->start = 0x1;
			else if (!ft_strcmp(line, "##end"))
				node->end = 0x1;
			continue ;
		}
		if (i >= 0)
		{
			if(!(node->links = (t_node *)ft_memalloc(sizeof(t_node))))
				return (NULL);
			node = node->links;
    }
		i = 0;
		while (line[i++] != ' ');
		line[i - 1] = 0;
		node->name = line;
	}
	return (line);
}

t_node			*ft_reader(t_data *data)
{
	char		*line;
	t_node	*node;
	t_node	*aux;

	if (get_next_line(data->fd, &line) < 0)
		ft_error("get next lain a fallado primoh");
	data->n_ants = ft_atoi(line);
	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		ft_error(NULL);
	aux = node;
	line = ft_ini_node(data, node, line);
	ft_set_links(data, line, aux);
	return (aux);
}
