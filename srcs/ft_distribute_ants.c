/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_distribute_ants.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:02:47 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/11 03:23:34 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**void	map_lector(t_map **conj, int len)
**{
**	t_path *aux;
**	t_map *aux2;
**
**	if (conj)
**	{
**		for (int i=0; i < len; i++)
**		{
**			aux2 = conj[i];
**			ft_printf("Conj %i\n", i);
**			for(int j=0; j < i + 1; j++)
**			{
**				ft_printf("Path %i:", j);
**				aux = aux2->path;
**				while (aux)
**				{
**					ft_printf("%s -", aux->node->name);
**					aux = aux->next;
**				}
**				ft_putchar('\n');
**				aux2 = aux2->next;
**			}
**		}
**	}
**}
*/

static int		choose_conj(t_map **conjs, int len, int n_ants)
{
	int i;
	int j;
	int h;
	int aux_h;
	int aux_i;

	i = len - 1;
	h = n_ants;
	aux_i = 0;
	while (i)
	{
		j = -1;
		while (++j < i)
		{
			if (conjs[i] && conjs[j] && (aux_h =
			ft_abs(ft_cuantity_of_ants(conjs[i], conjs[j], i + 1, j + 1))) < h)
			{
				if (!(h = aux_h))
					return (i);
				aux_i = i;
			}
		}
		i--;
	}
	return (aux_i);
}

static double	**allocate_matrix(int len)
{
	double	**mat;
	int		i;

	if (!(mat = (double **)malloc(sizeof(double *) * (len + 1))))
		ft_error(NULL);
	i = 0;
	while (i < len + 1)
	{
		if (!(mat[i++] = (double *)ft_memalloc(sizeof(double) * (len + 1))))
			ft_error(NULL);
	}
	return (mat);
}

static void		matrix_gen(t_map *conj, int n_path, double **mat)
{
	int		i;
	int		j;
	int		k;
	t_map	*mi;
	t_map	*mj;

	i = -1;
	k = 0;
	mi = conj;
	while (++i < n_path)
	{
		j = -1;
		mj = conj;
		while (++j < n_path && k < n_path)
		{
			if (i != j)
			{
				mat[k][i] = 1.0;
				mat[k][j] = -1.0;
				mat[k++][n_path] = mj->len - mi->len;
				mj = mj->next;
			}
		}
		mi = mi->next;
	}
}

void			ft_distribute_ants(t_data *data, t_map **conjs, int len)
{
	int		pos;
	double	**mat;
	int		i;

	pos = choose_conj(conjs, len, data->n_ants);
	mat = allocate_matrix(pos + 1);
	matrix_gen(conjs[pos], pos + 1, mat);
	i = 0;
	while (i < pos + 1)
		mat[pos + 1][i++] = 1.0;
	mat[pos + 1][pos + 1] = (double)data->n_ants;
	if (!ft_solve_system(mat, pos + 2, pos + 2))
		ft_error("No solution found");
	ft_solution(data, conjs[pos], mat, pos + 2);
	i = 0;
	while (i <= pos + 1)
		free(mat[i++]);
	free(mat);
}
/*
** for show the matrix
**	for(i = 0; i < pos + 2; i++)
**	{
**		for(int j = 0; j < pos + 2; j++)
**		{
**			ft_printf("%f ", (mat)[i][j]);
**		}
**		ft_printf("\n");
**	}
*/
