/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:04:22 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/16 07:37:07 by mrodrigu         ###   ########.fr       */
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

static int		check_comment_line(t_data *data, char *line, t_node *node)
{
	if (*line == 35)
	{
		if (!ft_strcmp(line, "##start"))
		{
			if (data->errors.start || !node)
				ft_error("Wrong number or position of ##start");
			node->start = 0x1;
			data->errors.start = 0x1;
		}
		else if (!ft_strcmp(line, "##end"))
		{
			if (data->errors.end || !node)
				ft_error("Wrong number or position of ##end");
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
		if (check_comment_line(data, line, NULL))
			goto next;
		else if (check_link_format(line))
			ft_error("Wrong link format");
		i = 0;
		while(line[i++] != '-');
		line[i - 1] = 0;
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

static char		*check_repeated_names(t_node *node, char *line)
{
	while (node)
	{
		if (node->name && !ft_strcmp(node->name, line))
			ft_error("Some name is repeated");
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
		if (check_comment_line(data, line, node))
			continue ;
		else if (check_node_format(line))
			ft_error("Wrong node format");
		if (i >= 0)
		{
			if(!(node->links = (t_node *)ft_memalloc(sizeof(t_node))))
				return (NULL);
			node = node->links;
    }
		i = 0;
		while (line[i++] != ' ');
		line[i - 1] = 0;
		node->name = check_repeated_names(head, line);
	}
	return (line);
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
			ft_error("First line should only contain numbers");
	}
	data->n_ants = ft_atoi(line);
	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		ft_error(NULL);
	line = ft_ini_node(data, node, line);
	if (!data->errors.start || !data->errors.end)
		ft_error("No start or end found");
	ft_set_links(data, line, node);
	return (node);
}
