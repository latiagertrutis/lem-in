/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:04:22 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/10 04:00:52 by mrodrigu         ###   ########.fr       */
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
	while (ft_strcmp(aux->name, s1) && aux)
		aux = aux->links;
	if (!(new_links = (t_node *)malloc(sizeof(t_node) * (aux->n_links + 2))))
		return ;
	i = -1;
	while (++i < aux->n_links + 1)
		new_links[i] = aux->links[i];
	aux2 = n;
	while (ft_strcmp(aux2->name, s2) && aux2)
		aux2 = aux2->links;
	new_links[i] = *aux2;
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
		line[i] = 0;
		ft_link(line, line + i + 1, n, data);
		free(line);
		next: if (get_next_line(data->fd, &line) <= 0)
			break ;
	}
}

static void		ft_ini_node(t_data *data, t_node *node, char *line)
{
	int		i;

	i = -1;
	while (get_next_line(data->fd, &line) > 0 && !ft_strchr(line, '-'))
	{
		if (i >= 0 && !(node = (t_node *)ft_memalloc(sizeof(t_node))))
			return ;
		if (*line == 35)
		{
			if (!ft_strcmp(line, "##start"))
				node->start = 0x1;
			else if (!ft_strcmp(line, "##end"))
				node->end = 0x1;
			i = -1;
			continue ;
		}
		i = 0;
		while (line[i++] != ' ');
		line[i] = 0;
		node->name = line;
		node = node->links;
	}
}

t_node			*ft_reader(t_data *data)
{
	char	*line;
	t_node	*node;
	t_node	*aux;

	if (get_next_line(data->fd, &line) < 0)
		ft_error("get next lain a fallado primoh");
	data->n_ants = ft_atoi(line);
	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		ft_error(NULL);
	aux = node;
	ft_ini_node(data, node, line);
	ft_set_links(data, line, aux);
	return (aux);
}
