/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:35:46 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/27 12:52:50 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int		compare_path(const t_node *node, t_path *path)
{
	while (path)
	{
		if (path->node == node)
			return (1);
		path = path->next;
	}
	return (0);
}

static void		show_path(t_path *path)
{
	while (path)
	{
		ft_printf("%s - ", path->node->name);
		path = path->next;
	}
	ft_printf("\n");
}

static t_map		*prepare_graf(t_node *node, t_map *map, int pos, int mode)
{
	t_path *path;
	t_map	*tmp;

	tmp = map;
	while (pos)
	{
		map = map->next;
		pos--;
	}
	path = map->path;
	map->len *= -1;
	show_path(path);
	while (node)
	{
		if ((node->ihbt && !mode && (node->ihbt != -1 || compare_path(node, path))) || node->end)
			node->ihbt = 0;
		else if (mode && node->ihbt != -1 && compare_path(node, path))
			node->ihbt = -1;
		else if (node->ihbt != -1)
			node->ihbt = 0;
		node = node->next;
	}
	while(tmp->next)
		tmp = tmp->next;
	
	return (tmp);
}
t_map	*ft_destroy_path(t_map **map)
{
	t_path	*aux;
	t_map	*tmp;
	t_map	*tmp2;

	tmp2 = *map;
	while ((*map)->next)
		(*map) = (*map)->next;
	while ((*map)->path)
	{
		aux = (*map)->path->next;
		free((*map)->path);
		(*map)->path = aux;
	}
	if ((*map)->prev)
	{
		(*map)->prev->next = NULL;
		tmp = (*map)->prev;
	}
	else
	{
		tmp = NULL;
		tmp2 = NULL;
	}
	free((*map));
	(*map) = tmp2;
	return (tmp);
}

static void	reset_graf(t_node *node, int *cuant)
{
	int	i;

	i = 0;
	while (node)
	{
		node->ihbt = 0;
		node = node->next;
	}
	*cuant = 0;
}

t_map	**ft_algorithm(t_data *data, t_node *node, int max)
{
	t_map	**conj;
	t_map	*prev;
	t_map	*tail;
	t_map	*head;
	int		i;
	int		j;
	int		k;
	int		tmp;
	int		cuant;
	int		tmp_cuant;

	prev = NULL;
	conj = (t_map **)ft_memalloc(sizeof(t_map *) * (max + 1));
//	cuant = (int *)ft_memalloc(sizeof(int) * (data->start->n_links + 1));
//	cuant[data->start->n_links] = -1;
	conj[max] = NULL;
	tmp = 0;
	i = 0;
	cuant = 0;
	j = max;
	tail = NULL;
	head = NULL;
	ft_printf("Debo tener %i conjuntos\n", max);
	while (i < data->start->n_links && i >= 0 && j > 0)
	{
		data->start->ihbt = 1;
		data->start->links[i]->start = 0x1;
		ft_printf("El proximo camino debera ser menor de %i\n", tmp);
//		if (!(conj[max - j] = ft_search_paths2(data->start->links[i], cuant + i, tmp)))
		if (!(conj[max - j] = ft_search_paths2(data->start->links[i], &tmp_cuant, &tmp)))
		{
			ft_printf("No he encontrado paths cuant vale %i\n",cuant);
			if (!i)
				ft_error("Start y Exit no unidos\n");
			i--;
			if (head)
			{
				conj[max - j] = head;
			}
			prev = NULL;
			ft_printf("cuant = %i\n", cuant);
//			tail = NULL;
			//		if (tail && tail->prev)
//			{
			if (tail->prev)
			{
				ft_printf("el inicio de tail es %s y el de lanterior es %s\n", tail->path->node->name, tail->prev->path->node->name);
			}
			
			if (!(cuant - 1) || tail->path->node->id != tail->prev->path->node->id)
			{
				if ((tmp = tail->len) < 0)
					tmp *= -1;
			}
//			}
			else
				tmp = 0;
			ft_printf("tmp vale %i\n", tmp);
			prepare_graf(node, conj[max - j], --cuant, 0);
//			if (cuant)
//			{
			ft_printf("Borro el camino %i\n", cuant);
			ft_printf("ANTES \n");
			ft_map_lector(conj[max - j], NULL);
			tail = ft_destroy_path(&head);
			ft_printf("Tras borrar la cola esta en:\n");
			if (tail)
			{
				show_path(tail->path);
			}
			ft_printf("DESPUES \n");
			ft_map_lector(head, NULL);
//			}
//			i--;
//			for(t_node *tmp = node; tmp; tmp = tmp->next)
			//		ft_printf("El nodo %s esta a %i\n", tmp->name, tmp->ihbt);
//			ft_error("No paths\n");
		}
		ft_printf("He encontrado %i caminos y tenia %i los que he encontrado son:\n", tmp_cuant, cuant);
		ft_map_lector(head,NULL);
		ft_printf("\n\n");
		
		data->start->links[i]->start = 0;
		/* if (!tmp_cuant && (tail->prev->path->node->id != tail->path->node->id)) */
		/* { */
		/* 	ft_printf("Ya no me quedan caminos y el anterior media %i\n", conj[max - j]->len); */
		/* 	tmp = conj[max - j]->len > 0 ? conj[max - j]->len : conj[max - j]->len * -1; */
		/* 	ft_destroy_path(conj[max - j], 0); */
		/* 	prev = NULL; */
		/* } */
		if (conj[max - j] && i + 1 == max - j + 1)
		{
			k = 0;
			ft_printf("He completado el conjunto %i\n", max - j);
			conj[max - j]->len *= -1;
			if (!head)
				head = conj[max - j];
			if (tail)
			{
				tail->next = conj[max - j];
				conj[max - j]->prev = tail;
			}
			/* while (conj[max - j]->prev) */
			/* { */
			/* 	ft_printf("Rebobino\n"); */
			/* 	conj[max - j] = conj[max - j]->prev; */
			/* } */
			conj[max - j] = head;
			ft_putstr("{{{{\n");
			ft_map_lector(conj[max - j], NULL);
			ft_putstr("}}}}\n");
			if (!conj[max - j]->next)
				ft_putstr("No hay next\n");
			head = NULL;
			tail = NULL;
			prev = NULL;
			reset_graf(node, &cuant);
			i = 0;
			j--;
		}
		else if (!tmp)
		{
			cuant += tmp_cuant;
			tmp_cuant = 0;
			ft_printf("Preparo siguiente camino cuant=%i\n", cuant);
			tmp = 0;
			ft_printf("Preparado camino %i\n", cuant);
			i++;
			if (!head)
				head = conj[max - j];
			/* ft_printf("Tail: \n"); */
			/* if (tail) */
			/* 	show_path(tail->path); */
			/* else */
			/* 	ft_printf("NULO\n"); */
			/* ft_printf("Head: \n"); */
			/* if (head) */
			/* 	show_path(head->path); */
			/* else */
			/* 	ft_printf("NULO\n"); */
			/* ft_printf("Conj: \n"); */
			/* if(conj[max - j]) */
			/* 	show_path(conj[max - j]->path); */
			/* else */
			/* 	ft_printf("NULO\n"); */
			if (tail && head != conj[max - j])
			{
				ft_printf("\n\n\n");
				tail->next = conj[max - j];
				//			ft_printf("Voy a poner el nodo %s detras\n", tail->path->node->name);
				conj[max - j]->prev = tail;
				ft_map_lector(head, NULL);
//				head = conj[max - j];
			}
			ft_putstr("[[[[\n");
			ft_map_lector(head, NULL);
			ft_putstr("]]]]\n");			
			tail = prepare_graf(node, head, cuant - 1, 1);
			ft_printf("La cola es:\n");
			show_path(tail->path);
//			prev = conj[max - j];
			prev = tail;
//			conj[max - j] = conj[max - j]->next;
			conj[max - j] = tail->next;
//			conj[max - j]->prev = prev;
		}
	}
	return (conj);
}
