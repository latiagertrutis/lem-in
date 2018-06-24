/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 18:22:38 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/24 20:30:46 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int 	search_pivot(double **mat, int j, int col)
{
	double max;
	int row;
	int i;

	max = ft_abs_double(mat[j][j]);
	i = j + 1;
	while (i < col - 1)
	{
		if (max < ft_abs_double(mat[i][j]))
		{
			max = ft_abs_double(mat[i][j]);
			row = i;
		}
		i++;
	}
	return (row);
}

static void	change_rows(double **mat, int j, int aux_r)
{
	double *aux;

	if (aux_r != j)
	{
		aux = mat[j];
		mat[j] = mat[aux_r];
		mat[aux_r] = aux;
	}
}

static void	normalize(double **mat, int j, int col)
{
	double piv;
	int i;

	piv = mat[j][j];
	i = j;
	while (i < col)
	{
		mat[j][i] = mat[j][i] / piv;
		i++;
	}
}

static void	put_zeros(double **mat, int j, int col)
{
	double factor;
	int i;
	int k;

	i = 1;
	while (i < col - 1)
	{
		if (i != j)
		{
			factor = mat[i][j];
			k = j;
			while (k < col)
			{
				mat[i][k] = mat[i][k] - (factor * mat[j][k]);
				k++;
			}
		}
		i++;
	}
}

void			distribute_ants(double **mat, int row, int col)
{
	int j;
	int aux_r;

	j = 0;
	while(1)
	{
		aux_r = search_pivot(mat, j, col);
		change_rows(mat, j, aux_r);
		normalize(mat, j, col);
		put_zeros(mat, j, col);
		j++;
		if (j == row)
			break ;
	}
}
