/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 12:45:32 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/08 22:00:57 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static	t_node	*search_node(t_node *head, char *line, t_data *data)
{
	int i;

	i = 0;
	while (head && (i = ft_strcmp(head->name, line)))
		head = head->next;
	if (i)
		ft_line_error(data->current_line, "Some name in links is wrong");
	return (head);
}

static void		append_link(t_node *a, t_node *b)
{
	if (a->n_links >= LINK_BUFF)
		resize_links(a);
	(a->links)[a->n_links] = b;
	a->n_links++;
}

static	void	ft_link(char *s1, char *s2, t_node *head, t_data *data)
{
	t_node	*aux;
	t_node	*aux2;

	aux = search_node(head, s1, data);
	aux2 = search_node(head, s2, data);
	append_link(aux, aux2);
	append_link(aux2, aux);
}

static int		format_line(char *line)
{
	int i;

	i = 0;
	while (line[i] != '-')
		i++;
	line[i] = 0;
	return (i);
}

void			ft_set_links(t_data *data, char *line, t_node *head)
{
	int i;

	while (1)
	{
		if (!line)
			ft_line_error(data->current_line, "No link found");
		data->current_line++;
		ft_print_map(data, line);
		if (check_comment_line(data, line, NULL))
		{
			free(line);
			if (get_next_line(data->fd, &line) <= 0)
				break ;
			continue ;
		}
		else if (check_link_format(line))
			ft_line_error(data->current_line, "Wrong link format");
		i = format_line(line);
		ft_link(line, line + i + 1, head, data);
		free(line);
		if (get_next_line(data->fd, &line) <= 0)
			break ;
	}
}
