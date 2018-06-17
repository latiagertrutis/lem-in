/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:04:22 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/17 10:06:19 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static	t_node	*search_node(t_node *n, char *line, t_data *data)
{
	int i;

	i = 0;
	while (n && (i = ft_strcmp(n->name, line)))
		n = n->links;
	if (i)
		ft_line_error(data->current_line, "Some name in links is wrong");
	return (n);
}

static void resize_links(t_node *n, t_node new_node)
{
	int 	i;
	t_node *link_arr;

	i = 0;
	if (!(link_arr = (t_node *)ft_memalloc(sizeof(t_node) * (n->n_links + 2))))
		ft_error(NULL);
	while (n->links && i < n->n_links + 1)
	{
		link_arr[i] = n->links[i];
		i++;
	}
	link_arr[n->n_links + 1] = new_node;
	free(n->links);
	n->links = link_arr;
	n->n_links++;
}

static	void	ft_link(char *s1, char *s2, t_node *n, t_data *data)
{
	t_node	*aux;
	t_node	*aux2;

	aux = search_node(n, s1, data);
	aux2 = search_node(n, s2, data);
	resize_links(aux, *aux2);
	resize_links(aux2, *aux);
}

static int		check_comment_line(t_data *data, char *line, t_node *node)
{
	if (*line == 35)
	{
		if (!ft_strcmp(line, "##start"))
		{
			if (data->errors.start || !node)
				ft_line_error(data->current_line, "Wrong number or position of ##start");
			node->start = 0x1;
			data->errors.start = 0x1;
		}
		else if (!ft_strcmp(line, "##end"))
		{
			if (data->errors.end || !node)
				ft_line_error(data->current_line, "Wrong number or position of ##end");
			node->end = 0x1;
			data->errors.end = 0x1;
		}
		return (1);
	}
	return (0);
}

static int		check_link_format(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '-')
	{
		if (line[i] < 33 || line[i] > 126)
			return (1);
		i++;
	}
	if (!line[i++])
		return(1);
	while (line[i] && line[i] != '-')
	{
		if (line[i] < 33 || line[i] > 126)
			return (1);
		i++;
	}
	return (0);
}

static	void	ft_set_links(t_data *data, char *line, t_node *n)
{
	int i;

	while (1)
	{
		data->current_line++;
		if (check_comment_line(data, line, NULL))
			goto next;
		else if (check_link_format(line))
			ft_line_error(data->current_line, "Wrong link format");
		i = 0;
		/* ft_putstr(line); */
		/* ft_putstr("\n"); */
		while(line[i++] != '-');
		line[i - 1] = 0;
		if (!ft_strcmp(line, line + i))
			ft_line_error(data->current_line, "Some node is linked with himselve");
		ft_link(line, line + i, n, data);
		free(line);
	next: if (get_next_line(data->fd, &line) <= 0)
			break ;
	}
}

static int		check_node_format(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] < 33 || line[i] > 126)
			return (1);
		i++;
	}
	if (!line[i++] || line[i] == ' ')
		return(1);
	while (line[i] && line[i] != ' ')
	{
		if (!ft_isdigit(line[i++]))
			return (1);
	}
	if (!line[i++] || line[i] == ' ')
		return(1);
	while (line[i])
	{
		if (!ft_isdigit(line[i++]))
			return (1);
	}
	return (0);
}

static char		*check_repeated_names(t_node *node, char *line, int current_line)
{
	while (node)
	{
		if (node->name && !ft_strcmp(node->name, line))
			ft_line_error(current_line, "Some name is repeated");
		node = node->links;
	}
	return (line);
}

static char		*ft_ini_node(t_data *data, t_node *node, char *line)
{
	int		i;
	t_node	*head;

	i = -1;
	head = node;
	while (get_next_line(data->fd, &line) > 0 && !ft_strchr(line, '-'))
	{
		data->current_line++;
		if (check_comment_line(data, line, node))
			continue ;
		else if (check_node_format(line))
			ft_line_error(data->current_line, "Wrong node format");
		if (i >= 0)
		{
			if(!(node->links = (t_node *)ft_memalloc(sizeof(t_node))))
				ft_error(NULL);
			node = node->links;
		}
		i = 0;
		while (line[i++] != ' ');
		line[i - 1] = 0;
		node->name = check_repeated_names(head, line, data->current_line);
		node->id = data->n_nodes++;
	}
	return (line);
}

static void 	check_conexions(t_node *node, t_data *data)
{
	int i;

	i = 0;
	while (i++ < data->n_nodes)
	{
		if (!node->n_links)
			ft_error("Node is not connected");
		if (node->start && !data->start)
		{
			node->start = 0;
			node->links->start = 0x1;
			data->start = node->links;
		}
		if (node->end && !data->end)
		{
			node->end = 0;
			node->links->end = 0x1;
			data->end = node->links;
		}
		node = node->links;
	}
}

t_node			*ft_reader(t_data *data)
{
	char		*line;
	t_node	*node;
	int			i;

	if (get_next_line(data->fd, &line) < 0)
		ft_error("get next lain a fallao primoh");
	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i++]))
			ft_line_error(data->current_line, "First line should only contain numbers");
	}
	data->n_ants = ft_atoi(line);
	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		ft_error(NULL);
	line = ft_ini_node(data, node, line);
	if (!data->errors.start || !data->errors.end)
		ft_line_error(data->current_line, "No start or end found");
	ft_set_links(data, line, node);
	/* t_node *no = node; */
	/* int c = 0; */
	/* while (no) */
	/* { */
	/* 	ft_putstr(no->name); */
	/* 	ft_putstr(": "); */
	/* 	c = 1; */
	/* 	while (no->links && c <= no->n_links) */
	/* 	{ */
	/* 		ft_putstr((no->links)[c++].name); */
	/* 		ft_putstr(", "); */
	/* 	} */
	/* 	ft_putstr("\n"); */
	/* 	no = no->links; */
	/* } */

	check_conexions(node, data);
	return (node);
}
