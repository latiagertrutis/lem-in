/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 12:23:36 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/20 19:39:01 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	check_node_format(char *line)
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
		return (1);
	while (line[i] && line[i] != ' ')
	{
		if (!ft_isdigit(line[i++]))
			return (1);
	}
	if (!line[i++] || line[i] == ' ')
		return (1);
	while (line[i])
	{
		if (!ft_isdigit(line[i++]))
			return (1);
	}
	return (0);
}

static char	*check_repeated_names(t_node *node, char *line, int current_line)
{
	while (node)
	{
		if (node->name && !ft_strcmp(node->name, line))
			ft_line_error(current_line, "Some name is repeated");
		node = node->next;
	}
	return (line);
}

static void	set_node(t_data *data, t_node *node, t_node *head, char *line)
{
	int i;

	i = 0;
	while (line[i] != ' ')
		i++;
	line[i] = 0;
	node->name = check_repeated_names(head, line, data->current_line);
	if (node->name[0] == 'L')
		ft_line_error(data->current_line, "Name starts with 'L'");
	node->id = data->n_nodes++;
	if (data->errors.start && !data->start)
	{
		node->start = 0x1;
		data->start = node;
	}
	if (data->errors.end && !data->end)
	{
		node->end = 0x1;
		data->end = node;
	}
	if (node->start && node->end)
		ft_line_error(data->current_line, "End and Start in the same node");
}

char		*ft_ini_node(t_data *data, t_node *node, char *line)
{
	t_node	*head;

	head = node;
	while (get_next_line(data->fd, &line) > 0 && !ft_strchr(line, '-'))
	{
		data->current_line++;
		if (check_comment_line(data, line, node))
			continue ;
		else if (check_node_format(line))
			ft_line_error(data->current_line, "Wrong node format");
		if (data->n_nodes)
		{
			if (!(node->next = (t_node *)ft_memalloc(sizeof(t_node))) ||
				!(node->next->links =
				(t_node **)ft_memalloc(sizeof(t_node *) * LINK_BUFF)))
				ft_error(NULL);
			node = node->next;
		}
		set_node(data, node, head, line);
	}
	return (line);
}
